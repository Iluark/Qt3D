#include "ProcessModelWithQt3D.h"
#include "ui_ProcessModelWithQt3D.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QDebug>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DRender/QPointLight>
#include <Qt3DExtras/QForwardRenderer>
#include <Qt3DRender/QCameraLens>
#include <Qt3DCore/QTransform>
#include <QColor>
#include <QMouseEvent>
#include <QtMath>


ProcessModelWithQt3D::ProcessModelWithQt3D(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ProcessModelWithQt3D)
    , m_3dWindow(nullptr)
    , m_rootEntity(nullptr)
    , m_camera(nullptr)
    , m_lightEntity(nullptr)
    , m_modelEntity(nullptr)
    , m_camController(nullptr)
    , m_mousePressed(false)
    , m_baseRotation(QQuaternion())
    , m_currentRotation(QQuaternion())
    , m_modelScale(1.0f)
    , m_modelCenter(0, 0, 0)
{
    ui->setupUi(this);

    // 初始化3D场景
    setup3DScene();
}

ProcessModelWithQt3D::~ProcessModelWithQt3D()
{
    delete ui;
}

void ProcessModelWithQt3D::setup3DScene()
{
    // 确保容器有布局
    if (!ui->model3DViewContainer->layout()) {
        auto *layout = new QVBoxLayout(ui->model3DViewContainer);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(0);
    }

    // 创建3D窗口并创建容器挂载到UI
    auto *view = new Qt3DExtras::Qt3DWindow();
    QWidget *container = QWidget::createWindowContainer(view, ui->model3DViewContainer);
    container->setFocusPolicy(Qt::StrongFocus);
    
    // 安装事件过滤器来处理鼠标事件
    container->installEventFilter(this);

    ui->model3DViewContainer->layout()->addWidget(container);
    m_3dWindow = view;

    // 创建根实体
    m_rootEntity = new Qt3DCore::QEntity();

    // 设置相机（固定位置，不再移动）
    m_camera = m_3dWindow->camera();
    m_camera->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    m_camera->setPosition(QVector3D(0, 0, 50.0f));
    m_camera->setViewCenter(QVector3D(0, 0, 0));
    m_camera->setUpVector(QVector3D(0, 1, 0));

    // 添加主光源（从相机位置照射）
    m_lightEntity = new Qt3DCore::QEntity(m_rootEntity);
    auto *mainLight = new Qt3DRender::QPointLight(m_lightEntity);
    mainLight->setColor("white");
    mainLight->setIntensity(0.8f);
    m_lightEntity->addComponent(mainLight);
    auto *lightTransform = new Qt3DCore::QTransform(m_lightEntity);
    lightTransform->setTranslation(QVector3D(0, 0, 50.0f));
    m_lightEntity->addComponent(lightTransform);
    
    // 添加辅助光源（环境光效果）
    auto *auxLightEntity = new Qt3DCore::QEntity(m_rootEntity);
    auto *auxLight = new Qt3DRender::QPointLight(auxLightEntity);
    auxLight->setColor(QColor(200, 220, 255)); // 淡蓝色辅助光
    auxLight->setIntensity(0.3f);
    auxLightEntity->addComponent(auxLight);
    auto *auxLightTransform = new Qt3DCore::QTransform(auxLightEntity);
    auxLightTransform->setTranslation(QVector3D(-30, 30, 30));
    auxLightEntity->addComponent(auxLightTransform);

    // 移除相机控制器（我们用自定义鼠标控制）
    // m_camController = new Qt3DExtras::QOrbitCameraController(m_rootEntity);

    // 设置更舒适的背景色（深蓝灰色）
    if (auto *renderer = m_3dWindow->defaultFrameGraph()) {
        renderer->setClearColor(QColor(45, 52, 65)); // 现代深色主题背景
    }

    // 设置场景
    m_3dWindow->setRootEntity(m_rootEntity);
}

void ProcessModelWithQt3D::loadSTLModel(const QString& filePath)
{
    // 清理旧模型
    if (m_modelEntity) {
        m_modelEntity->deleteLater();
        m_modelEntity = nullptr;
        m_modelTransform = nullptr;
    }

    // 创建新模型实体
    m_modelEntity = new Qt3DCore::QEntity(m_rootEntity);

    // 创建场景加载器
    auto *sceneLoader = new Qt3DRender::QSceneLoader(m_modelEntity);
    sceneLoader->setSource(QUrl::fromLocalFile(filePath));

    // 创建更现代的材质（蓝色调金属质感）
    auto *material = new Qt3DExtras::QPhongMaterial(m_modelEntity);
    material->setDiffuse(QColor(70, 130, 180));    // 钢蓝色
    material->setSpecular(QColor(200, 200, 255));  // 白色高光
    material->setShininess(50.0f);                 // 适中光泽度
    material->setAmbient(QColor(30, 60, 90));      // 深蓝色环境光

    // 创建变换组件
    m_modelTransform = new Qt3DCore::QTransform(m_modelEntity);

    // 添加到实体
    m_modelEntity->addComponent(sceneLoader);
    m_modelEntity->addComponent(material);
    m_modelEntity->addComponent(m_modelTransform);

    // 重置模型变换
    resetModelTransform();
    
    qDebug() << "模型已加载:" << filePath;
}

void ProcessModelWithQt3D::resetModelTransform()
{
    if (!m_modelTransform) return;
    
    // 重置旋转和缩放
    m_baseRotation = QQuaternion();
    m_currentRotation = QQuaternion();
    m_modelScale = 1.0f;
    m_modelCenter = QVector3D(0, 0, 0);
    
    // 应用默认的模型适配（可以根据需要调整）
    m_modelTransform->setScale(10.0f); // STL模型通常需要放大
    m_modelTransform->setTranslation(QVector3D(0, 0, 0));
    m_modelTransform->setRotation(QQuaternion());
}

void ProcessModelWithQt3D::updateModelTransform()
{
    if (!m_modelTransform) return;
    
    // 组合基础旋转和当前旋转
    QQuaternion finalRotation = m_currentRotation * m_baseRotation;
    
    m_modelTransform->setRotation(finalRotation);
    m_modelTransform->setScale(10.0f * m_modelScale); // 保持基础缩放
}

bool ProcessModelWithQt3D::eventFilter(QObject *watched, QEvent *event)
{
    if (!m_modelTransform) {
        return QWidget::eventFilter(watched, event);
    }
    
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::LeftButton) {
            m_mousePressed = true;
            m_lastMousePos = mouseEvent->pos();
            return true;
        }
    }
    else if (event->type() == QEvent::MouseButtonRelease) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::LeftButton) {
            m_mousePressed = false;
            // 将当前旋转合并到基础旋转中
            m_baseRotation = m_currentRotation * m_baseRotation;
            m_currentRotation = QQuaternion();
            return true;
        }
    }
    else if (event->type() == QEvent::MouseMove) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        if (m_mousePressed) {
            QPoint delta = mouseEvent->pos() - m_lastMousePos;
            
            // 计算旋转增量，固定旋转轴（X轴上下，Y轴左右）
            float rotationSpeed = 0.5f;
            float yawAngle = -delta.x() * rotationSpeed;   // 绕Y轴旋转（左右拖拽）
            float pitchAngle = delta.y() * rotationSpeed;  // 绕X轴旋转（上下拖拽）
            
            // 创建旋转四元数（固定世界坐标系的轴）
            QQuaternion yawRotation = QQuaternion::fromAxisAndAngle(QVector3D(0, 1, 0), yawAngle);
            QQuaternion pitchRotation = QQuaternion::fromAxisAndAngle(QVector3D(1, 0, 0), pitchAngle);
            
            // 组合旋转（先pitch后yaw）
            m_currentRotation = yawRotation * pitchRotation * m_currentRotation;
            
            // 更新模型变换
            updateModelTransform();
            
            m_lastMousePos = mouseEvent->pos();
            return true;
        }
    }
    else if (event->type() == QEvent::Wheel) {
        QWheelEvent *wheelEvent = static_cast<QWheelEvent*>(event);
        
        // 鼠标滚轮控制模型缩放
        float scaleFactor = 1.0f + (wheelEvent->angleDelta().y() > 0 ? 0.1f : -0.1f);
        m_modelScale = qMax(0.1f, qMin(5.0f, m_modelScale * scaleFactor));
        
        updateModelTransform();
        return true;
    }
    
    return QWidget::eventFilter(watched, event);
}

void ProcessModelWithQt3D::on_load3DModelBtn_clicked()
{
    // 加载STL文件
    QString filePath = QFileDialog::getOpenFileName(
        this, 
        "选择3D模型文件", 
        "", 
        "STL文件 (*.stl);;OBJ文件 (*.obj);;所有文件 (*)"
    );
    
    if(filePath.isEmpty()){
        qDebug() << "用户取消了文件选择";
        return;
    }

    loadSTLModel(filePath);
}

void ProcessModelWithQt3D::on_directionComboBox_currentIndexChanged(int index)
{
    if (!m_modelTransform) return;

    // 重置到标准方位，提供更准确的方向视图
    m_currentRotation = QQuaternion();
    
    QQuaternion rotation;
    switch (index) {
    case 0: // +X 视图（从X正方向看向原点）
        rotation = QQuaternion::fromAxisAndAngle(QVector3D(0, 1, 0), -90.0f);
        break;
    case 1: // -X 视图（从X负方向看向原点）
        rotation = QQuaternion::fromAxisAndAngle(QVector3D(0, 1, 0), 90.0f);
        break;
    case 2: // +Y 视图（从Y正方向看向原点，即俯视图）
        rotation = QQuaternion::fromAxisAndAngle(QVector3D(1, 0, 0), 90.0f);
        break;
    case 3: // -Y 视图（从Y负方向看向原点，即仰视图）
        rotation = QQuaternion::fromAxisAndAngle(QVector3D(1, 0, 0), -90.0f);
        break;
    case 4: // +Z 视图（从Z正方向看向原点，即正视图）
        rotation = QQuaternion();
        break;
    case 5: // -Z 视图（从Z负方向看向原点）
        rotation = QQuaternion::fromAxisAndAngle(QVector3D(0, 1, 0), 180.0f);
        break;
    case 6: // Origin（等距视图，45度角）
    default:
        rotation = QQuaternion::fromAxisAndAngle(QVector3D(1, 0, 0), -20.0f) * 
                  QQuaternion::fromAxisAndAngle(QVector3D(0, 1, 0), -30.0f);
        break;
    }
    
    m_baseRotation = rotation;
    updateModelTransform();
    
    qDebug() << "切换到视图方向:" << index;
}

void ProcessModelWithQt3D::on_createGrayImage_clicked()
{
    // 灰度图生成实现
    QMessageBox::information(this, "灰度图生成", "灰度图生成功能正在开发中...\n\n预计功能：\n• 深度图生成\n• 轮廓投影\n• 截面图像");
}

void ProcessModelWithQt3D::on_saveGrayImage_clicked()
{
    if (grayImage.isNull()) {
        QMessageBox::warning(this, "保存失败", "没有可保存的灰度图像\n请先生成灰度图");
        return;
    }

    QString filePath = QFileDialog::getSaveFileName(
        this,
        "保存灰度图",
        "gray_image.png",
        "PNG图像 (*.png);;JPEG图像 (*.jpg *.jpeg);;BMP图像 (*.bmp)"
        );

    if (!filePath.isEmpty()) {
        if (grayImage.save(filePath)) {
            QMessageBox::information(this, "保存成功", "灰度图已成功保存到:\n" + filePath);
        } else {
            QMessageBox::critical(this, "保存失败", "无法保存文件到:\n" + filePath);
        }
    }
}

// 辅助方法实现（为将来功能扩展预留）
QVector3D ProcessModelWithQt3D::calculateModelCenter()
{
    // TODO: 实现模型中心点计算
    return QVector3D(0, 0, 0);
}

float ProcessModelWithQt3D::calculateModelScale()
{
    // TODO: 实现模型自适应缩放计算
    return 1.0f;
}

void ProcessModelWithQt3D::fitModelToView()
{
    // TODO: 实现模型自适应视图功能
}

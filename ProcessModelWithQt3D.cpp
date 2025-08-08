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
#include <QFileInfo>


ProcessModelWithQt3D::ProcessModelWithQt3D(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ProcessModelWithQt3D)
    , m_3dWindow(nullptr)
    , m_rootEntity(nullptr)
    , m_camera(nullptr)
    , m_lightEntity(nullptr)
    , m_modelEntity(nullptr)
    , m_camController(nullptr)
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

    // 创建3D窗口容器
    QWidget *container = QWidget::createWindowContainer(new Qt3DExtras::Qt3DWindow(), ui->model3DViewContainer);
    container->setFocusPolicy(Qt::StrongFocus);

    ui->model3DViewContainer->layout()->addWidget(container);
    m_3dWindow = qobject_cast<Qt3DExtras::Qt3DWindow*>(container->window());

    // 创建根实体
    m_rootEntity = new Qt3DCore::QEntity();

    // 设置相机
    m_camera = m_3dWindow->camera();
    m_camera->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    m_camera->setPosition(QVector3D(0, 0, 40.0f));
    m_camera->setViewCenter(QVector3D(0, 0, 0));

    // 添加光源
    m_lightEntity = new Qt3DCore::QEntity(m_rootEntity);
    auto *light = new Qt3DRender::QPointLight(m_lightEntity);
    light->setColor("white");
    light->setIntensity(1.0f);
    m_lightEntity->addComponent(light);
    auto *lightTransform = new Qt3DCore::QTransform(m_lightEntity);
    lightTransform->setTranslation(QVector3D(0, 0, 40.0f));
    m_lightEntity->addComponent(lightTransform);

    // 添加相机控制器
    m_camController = new Qt3DExtras::QOrbitCameraController(m_rootEntity);
    m_camController->setCamera(m_camera);
    m_camController->setLinearSpeed(50.0f);
    m_camController->setLookSpeed(180.0f);

    // 背景色（在 Qt 6 中默认帧图类型可能不同，做安全转换）
    if (auto *fgNode = m_3dWindow->defaultFrameGraph()) {
        if (auto *forwardRenderer = qobject_cast<Qt3DExtras::QForwardRenderer*>(fgNode)) {
            forwardRenderer->setClearColor(QColor(0x20, 0x20, 0x20));
        }
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

    // 创建场景加载器（确保文件存在）
    if (!QFileInfo::exists(filePath)) {
        qWarning() << "STL 文件不存在:" << filePath;
        return;
    }
    auto *sceneLoader = new Qt3DRender::QSceneLoader(m_modelEntity);
    sceneLoader->setSource(QUrl::fromLocalFile(filePath));

    // 创建材质
    auto *material = new Qt3DExtras::QPhongMaterial(m_modelEntity);
    material->setDiffuse(QColor(QRgb(0x928327)));

    // 变换
    m_modelTransform = new Qt3DCore::QTransform(m_modelEntity);

    // 添加到实体
    m_modelEntity->addComponent(sceneLoader);
    m_modelEntity->addComponent(material);
    m_modelEntity->addComponent(m_modelTransform);

    // 重置相机位置
    m_camera->setPosition(QVector3D(0, 0, 40.0f));
    m_camera->setViewCenter(QVector3D(0, 0, 0));
}

void ProcessModelWithQt3D::on_load3DModelBtn_clicked()
{
    // 加载STL文件
    QString filePath = QFileDialog::getOpenFileName(this, "打开文件", "", ("*.stl"));
    if(filePath.isEmpty()){
        qDebug() << "文件加载失败";
        return;
    }

    loadSTLModel(filePath);
}

void ProcessModelWithQt3D::on_directionComboBox_currentIndexChanged(int index)
{
    if (!m_modelTransform) return;

    // 根据选择的方向调整模型朝向
    QQuaternion rotation;
    switch (index) {
    case 0: // +X
        rotation = QQuaternion::fromAxisAndAngle(QVector3D(0, 1, 0), -90.0f);
        break;
    case 1: // -X
        rotation = QQuaternion::fromAxisAndAngle(QVector3D(0, 1, 0), 90.0f);
        break;
    case 2: // +Y
        rotation = QQuaternion::fromAxisAndAngle(QVector3D(1, 0, 0), 90.0f);
        break;
    case 3: // -Y
        rotation = QQuaternion::fromAxisAndAngle(QVector3D(1, 0, 0), -90.0f);
        break;
    case 4: // +Z
        rotation = QQuaternion();
        break;
    case 5: // -Z
        rotation = QQuaternion::fromAxisAndAngle(QVector3D(0, 1, 0), 180.0f);
        break;
    case 6: // Origin (重置)
    default:
        rotation = QQuaternion();
        break;
    }
    m_modelTransform->setRotation(rotation);
}

void ProcessModelWithQt3D::on_createGrayImage_clicked()
{
    // 灰度图生成实现
    QMessageBox::information(this, "灰度图", "灰度图生成功能待实现");
}

void ProcessModelWithQt3D::on_saveGrayImage_clicked()
{
    if (grayImage.isNull()) {
        qDebug() << "没有可保存的灰度图";
        return;
    }

    QString filePath = QFileDialog::getSaveFileName(
        this,
        "保存灰度图",
        "",
        "PNG图像 (*.png);;JPEG图像 (*.jpg *.jpeg)"
        );

    if (!filePath.isEmpty()) {
        if (grayImage.save(filePath)) {
            qDebug() << "灰度图已保存到:" << filePath;
        } else {
            qDebug() << "保存失败:" << filePath;
        }
    }
}

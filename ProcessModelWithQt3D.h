#ifndef PROCESSMODELWITHQT3D_H
#define PROCESSMODELWITHQT3D_H

#include <QWidget>
#include <Qt3DCore/QEntity>
#include <Qt3DRender/QCamera>
#include <Qt3DExtras/QOrbitCameraController>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DRender/QSceneLoader>
#include <QUrl>
#include <Qt3DCore/QTransform>
#include <QImage>
#include <QMouseEvent>
#include <QVector3D>
#include <QQuaternion>


namespace Ui {
class ProcessModelWithQt3D;
}

class ProcessModelWithQt3D : public QWidget
{
    Q_OBJECT

public:
    explicit ProcessModelWithQt3D(QWidget *parent = nullptr);
    ~ProcessModelWithQt3D();

private slots:
    void on_load3DModelBtn_clicked();

    void on_directionComboBox_currentIndexChanged(int index);

    void on_createGrayImage_clicked();

    void on_saveGrayImage_clicked();

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    Ui::ProcessModelWithQt3D *ui;

    // Qt3D 相关成员
    Qt3DExtras::Qt3DWindow *m_3dWindow;
    Qt3DCore::QEntity *m_rootEntity;
    Qt3DRender::QCamera *m_camera;
    Qt3DCore::QEntity *m_lightEntity;
    Qt3DCore::QEntity *m_modelEntity;
    Qt3DExtras::QOrbitCameraController *m_camController;

    void setup3DScene();
    void loadSTLModel(const QString& filePath);

    QImage grayImage; // 存储生成的灰度图

    // 模型的变换（用于旋转/缩放/平移）
    Qt3DCore::QTransform *m_modelTransform = nullptr;
    
    // 鼠标控制相关
    bool m_mousePressed = false;
    QPoint m_lastMousePos;
    QQuaternion m_baseRotation;
    QQuaternion m_currentRotation;
    
    // 模型属性
    float m_modelScale = 1.0f;
    QVector3D m_modelCenter;
    
    // 辅助方法
    void resetModelTransform();
    void updateModelTransform();
    void fitModelToView();
    QVector3D calculateModelCenter();
    float calculateModelScale();
};

#endif // PROCESSMODELWITHQT3D_H

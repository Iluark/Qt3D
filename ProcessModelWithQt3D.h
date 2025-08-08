#ifndef PROCESSMODELWITHQT3D_H
#define PROCESSMODELWITHQT3D_H

#include <QWidget>
#include <Qt3DCore/QEntity>
#include <Qt3DRender/QCamera>
#include <Qt3DExtras/QOrbitCameraController>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DRender/QSceneLoader>
#include <QUrl>



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
};

#endif // PROCESSMODELWITHQT3D_H

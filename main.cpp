#include "mainwindow.h"
#include "Process3DWidget.h"
#include "ProcessModelWithQt3D.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 确保VTK使用正确的OpenGL后端
    QSurfaceFormat::setDefaultFormat(QVTKOpenGLNativeWidget::defaultFormat());

    //MainWindow w;
    //Process3DWidget w;
    ProcessModelWithQt3D w;
    w.show();
    return a.exec();
}

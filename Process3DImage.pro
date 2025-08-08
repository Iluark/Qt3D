QT       += core gui opengl widgets openglwidgets 3dcore 3drender 3dextras 3dinput

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 opengl
QMAKE_PROJECT_DEPTH = 0

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Process3DWidget.cpp \
    ProcessModelWithQt3D.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Process3DWidget.h \
    ProcessModelWithQt3D.h \
    mainwindow.h

FORMS += \
    Process3DWidget.ui \
    ProcessModelWithQt3D.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# 根据构建类型选择VTK路径
CONFIG(debug, debug|release) {
    VTK_DIR = "D:/QtProject/Process3DImage/VTK-9.5.0/VTK_debug"
} else {
    VTK_DIR = "D:/QtProject/Process3DImage/VTK-9.5.0/VTK_release"
}

# 包含路径
INCLUDEPATH += $${VTK_DIR}/include/vtk-9.5

# 库路径
LIBS += -L$${VTK_DIR}/lib

# 链接必要的VTK库
debug {
    LIBS += -lvtkCommonCore-9.5d
    LIBS += -lvtkCommonDataModel-9.5d
    LIBS += -lvtkCommonExecutionModel-9.5d
    LIBS += -lvtkFiltersCore-9.5d
    LIBS += -lvtkFiltersSources-9.5d
    LIBS += -lvtkGUISupportQt-9.5d
    LIBS += -lvtkIOGeometry-9.5d
    LIBS += -lvtkInteractionStyle-9.5d
    LIBS += -lvtkRenderingCore-9.5d
    LIBS += -lvtkRenderingOpenGL2-9.5d
    LIBS += -lvtksys-9.5d
    LIBS += -lvtkCommonTransforms-9.5d
    LIBS += -lvtkImagingCore-9.5d
    LIBS += -lvtkImagingSources-9.5d
}
else {
    LIBS += -lvtkCommonCore-9.5
    LIBS += -lvtkCommonDataModel-9.5
    LIBS += -lvtkCommonExecutionModel-9.5
    LIBS += -lvtkFiltersCore-9.5
    LIBS += -lvtkFiltersSources-9.5
    LIBS += -lvtkGUISupportQt-9.5
    LIBS += -lvtkIOGeometry-9.5
    LIBS += -lvtkInteractionStyle-9.5
    LIBS += -lvtkRenderingCore-9.5
    LIBS += -lvtkRenderingOpenGL2-9.5
    LIBS += -lvtksys-9.5
    LIBS += -lvtkCommonTransforms-9.5
    LIBS += -lvtkImagingCore-9.5
    LIBS += -lvtkImagingSources-9.5
}


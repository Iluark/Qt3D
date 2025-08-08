QT       += core gui widgets 3dcore 3drender 3dextras 3dinput

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    ProcessModelWithQt3D.cpp \
    main.cpp

HEADERS += \
    ProcessModelWithQt3D.h

FORMS += \
    ProcessModelWithQt3D.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


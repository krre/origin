QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OctreeFarm
TEMPLATE = app

INCLUDEPATH += "../../ThirdParty"

SOURCES += main.cpp\
        MainWindow.cpp \
    ControlsWidget.cpp \
    Octree.cpp \
    Camera.cpp \
    Viewport.cpp

HEADERS  += MainWindow.h \
    ControlsWidget.h \
    Octree.h \
    Camera.h \
    Viewport.h

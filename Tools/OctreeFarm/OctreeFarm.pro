QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OctreeFarm
TEMPLATE = app

INCLUDEPATH += "../../ThirdParty"

SOURCES += main.cpp\
        MainWindow.cpp \
    Octree.cpp \
    Camera.cpp \
    Viewport.cpp \
    Properties.cpp

HEADERS  += MainWindow.h \
    Octree.h \
    Camera.h \
    Viewport.h \
    Properties.h \
    ../../Source/Core/Common.h

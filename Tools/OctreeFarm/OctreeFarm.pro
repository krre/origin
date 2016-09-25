QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OctreeFarm
TEMPLATE = app

INCLUDEPATH += "../../ThirdParty"

SOURCES += main.cpp\
        MainWindow.cpp \
    GLWidget.cpp \
    ControlsWidget.cpp

HEADERS  += MainWindow.h \
    GLWidget.h \
    ControlsWidget.h

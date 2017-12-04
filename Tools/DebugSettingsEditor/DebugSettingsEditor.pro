QT += core gui widgets

CONFIG += c++11
TARGET = DebugSettingsEditor
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        main.cpp \
        MainWindow.cpp

HEADERS += \
        MainWindow.h \
    Defines.h

FORMS += \
        MainWindow.ui

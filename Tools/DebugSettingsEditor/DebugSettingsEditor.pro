QT += widgets
CONFIG += c++11
TARGET = DebugSettingsEditor
TEMPLATE = app
DESTDIR = $$(ORIGIN_HOME)

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        main.cpp \
        MainWindow.cpp \
    GeneralTab.cpp

HEADERS += \
        MainWindow.h \
    Defines.h \
    GeneralTab.h

FORMS += \
        MainWindow.ui \
    GeneralTab.ui

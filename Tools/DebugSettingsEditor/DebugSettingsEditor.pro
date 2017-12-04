QT += widgets
CONFIG += c++11
TARGET = DebugSettingsEditor
TEMPLATE = app
DESTDIR = $$(ORIGIN_HOME)

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        main.cpp \
        MainWindow.cpp \
    GeneralTab.cpp \
    VulkanTab.cpp

HEADERS += \
        MainWindow.h \
    Defines.h \
    GeneralTab.h \
    VulkanTab.h

FORMS += \
        MainWindow.ui \
    GeneralTab.ui \
    VulkanTab.ui

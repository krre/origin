QT += widgets
CONFIG += c++17
TARGET = DebugSettingsEditor
TEMPLATE = app
DESTDIR = $$(ORIGIN_HOME)

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += ../../../origin/Source
INCLUDEPATH += ../../../origin/Libs
INCLUDEPATH += $$(VULKAN_SDK)/include

unix:LIBS += -L$$(VULKAN_SDK)/lib -lvulkan
win32:LIBS += -L$$(VULKAN_SDK)/lib32 -lvulkan-1
LIBS += -L$$(ORIGIN_HOME) -lvulkanrenderer

SOURCES += \
    main.cpp \
    MainWindow.cpp \
    GeneralTab.cpp \
    VulkanTab.cpp

HEADERS += \
    MainWindow.h \
    Defines.h \
    GeneralTab.h \
    VulkanTab.h \
    AbstractTab.h

FORMS += \
    MainWindow.ui \
    GeneralTab.ui \
    VulkanTab.ui

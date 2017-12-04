QT += widgets
CONFIG += c++14
TARGET = DebugSettingsEditor
TEMPLATE = app
DESTDIR = $$(ORIGIN_HOME)

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += ../../../origin/Source
INCLUDEPATH += $$(VULKAN_SDK)/include

LIBS += -L$$(VULKAN_SDK)/lib -lvulkan

SOURCES += \
    main.cpp \
    MainWindow.cpp \
    GeneralTab.cpp \
    VulkanTab.cpp \
    ../../Source/Graphics/Vulkan/Instance.cpp \
    ../../Source/Graphics/Vulkan/DebugReportCallback.cpp

HEADERS += \
    MainWindow.h \
    Defines.h \
    GeneralTab.h \
    VulkanTab.h \
    AbstractTab.h \
    ../../Source/Graphics/Vulkan/Instance.h \
    ../../Source/Graphics/Vulkan/DebugReportCallback.h

FORMS += \
    MainWindow.ui \
    GeneralTab.ui \
    VulkanTab.ui

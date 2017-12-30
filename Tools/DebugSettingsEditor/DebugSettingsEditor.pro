QT += widgets
CONFIG += c++14
TARGET = DebugSettingsEditor
TEMPLATE = app
DESTDIR = $$(ORIGIN_HOME)

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += ../../../origin/Source
INCLUDEPATH += $$(VULKAN_SDK)/include

unix:LIBS += -L$$(VULKAN_SDK)/lib -lvulkan
win32:LIBS += -L$$(VULKAN_SDK)/lib32 -lvulkan-1

SOURCES += \
    main.cpp \
    MainWindow.cpp \
    GeneralTab.cpp \
    VulkanTab.cpp \
    ../../Source/Graphics/Vulkan/Wrapper/Instance.cpp \
    ../../Source/Graphics/Vulkan/Wrapper/DebugReportCallback.cpp

HEADERS += \
    MainWindow.h \
    Defines.h \
    GeneralTab.h \
    VulkanTab.h \
    AbstractTab.h \
    ../../Source/Graphics/Vulkan/Wrapper/Instance.h \
    ../../Source/Graphics/Vulkan/Wrapper/DebugReportCallback.h

FORMS += \
    MainWindow.ui \
    GeneralTab.ui \
    VulkanTab.ui

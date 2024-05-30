QT += widgets
CONFIG += c++20
TARGET = dse
TEMPLATE = app
DESTDIR = $$(ORIGIN_HOME)

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += ../../../origin/source
INCLUDEPATH += ../../../origin/libs
INCLUDEPATH += $$(VULKAN_SDK)/include

unix:LIBS += -L$$(VULKAN_SDK)/lib -lvulkan
win32:LIBS += -L$$(VULKAN_SDK)/lib32 -lvulkan-1
LIBS += -L$$(ORIGIN_HOME) -lvulkan-o

SOURCES += \
    Application.cpp \
    main.cpp \
    MainWindow.cpp \
    GeneralTab.cpp \
    VulkanTab.cpp

HEADERS += \
    Application.h \
    MainWindow.h \
    GeneralTab.h \
    VulkanTab.h \
    AbstractTab.h

FORMS += \
    MainWindow.ui \
    GeneralTab.ui \
    VulkanTab.ui

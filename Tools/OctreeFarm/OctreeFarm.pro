QT += widgets
QT += core-private gui-private # For use QPA
CONFIG += c++17
TARGET = OctreeFarm
TEMPLATE = app
DESTDIR = $$(ORIGIN_HOME)

INCLUDEPATH += "../../ThirdParty"
INCLUDEPATH += ../../../origin/Libs
INCLUDEPATH += $$(VULKAN_SDK)/include

unix:LIBS += -L$$(VULKAN_SDK)/lib -lvulkan
win32:LIBS += -L$$(VULKAN_SDK)/lib32 -lvulkan-1
LIBS += -L$$(ORIGIN_HOME) -lVulkanRenderer -lOctree

SOURCES += main.cpp\
    Octree.cpp \
    Camera.cpp \
    Viewport.cpp \
    Source.cpp \
    Command.cpp \
    MainWindow.cpp \
    VulkanRenderer.cpp \
    Properties.cpp \
    Options.cpp

HEADERS  += \
    Octree.h \
    Camera.h \
    Viewport.h \
    Source.h \
    Defines.h \
    Command.h \
    Origin.h \
    MainWindow.h \
    VulkanRenderer.h \
    Properties.h \
    Options.h

FORMS += \
    MainWindow.ui \
    Properties.ui \
    Options.ui

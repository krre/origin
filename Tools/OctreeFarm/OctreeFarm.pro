QT += widgets
CONFIG += c++17
TARGET = OctreeFarm
TEMPLATE = app

INCLUDEPATH += "../../ThirdParty"
INCLUDEPATH += ../../../origin/Libs
INCLUDEPATH += $$(VULKAN_SDK)/include

unix:LIBS += -L$$(VULKAN_SDK)/lib -lvulkan
win32:LIBS += -L$$(VULKAN_SDK)/lib32 -lvulkan-1
LIBS += -L$$(ORIGIN_HOME) -lVulkanRenderer

SOURCES += main.cpp\
    MainWindow.cpp \
    Octree.cpp \
    Camera.cpp \
    Viewport.cpp \
    Properties.cpp \
    Source.cpp \
    Command.cpp \
    OptionsDialog.cpp

HEADERS  += MainWindow.h \
    Octree.h \
    Camera.h \
    Viewport.h \
    Properties.h \
    Source.h \
    Defines.h \
    Command.h \
    OptionsDialog.h \
    Origin.h

QT += widgets
CONFIG += c++20
TARGET = OctreeFarm
TEMPLATE = app
DESTDIR = $$(ORIGIN_HOME)

INCLUDEPATH += "../../ThirdParty"
INCLUDEPATH += ../../Libs
INCLUDEPATH += $$(VULKAN_SDK)/include

unix:LIBS += -L$$(VULKAN_SDK)/lib -lvulkan
win32:LIBS += -L$$(VULKAN_SDK)/lib32 -lvulkan-1
LIBS += -L$$(ORIGIN_HOME) -lCore -lVulkan -lOctree

SOURCES += main.cpp\
    Camera.cpp \
    Viewport.cpp \
    Source.cpp \
    Command.cpp \
    MainWindow.cpp \
    Properties.cpp \
    Options.cpp \
    RenderEngine.cpp \
    Settings.cpp \
    OctreeEditor.cpp

HEADERS  += \
    Camera.h \
    Viewport.h \
    Source.h \
    Defines.h \
    Command.h \
    Origin.h \
    MainWindow.h \
    Properties.h \
    Options.h \
    RenderEngine.h \
    Settings.h \
    OctreeEditor.h \
    Constants.h

FORMS += \
    MainWindow.ui \
    Properties.ui \
    Options.ui

DISTFILES += \
    ../../Data/Shader/OctreeFarm/FrontLightOctree.frag \
    ../../Data/Shader/OctreeFarm/FrontLightOctree.vert

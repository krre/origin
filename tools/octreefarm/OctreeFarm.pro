QT += widgets
CONFIG += c++20
TARGET = octreefarm
TEMPLATE = app
DESTDIR = $$(ORIGIN_HOME)

INCLUDEPATH += "../../trdparty"
INCLUDEPATH += ../../libs
INCLUDEPATH += $$(VULKAN_SDK)/include

unix:LIBS += -L$$(VULKAN_SDK)/lib -lvulkan
win32:LIBS += -L$$(VULKAN_SDK)/lib32 -lvulkan-1
LIBS += -L$$(ORIGIN_HOME) -lcore -lvulkan-o -loctree

SOURCES += main.cpp\
    Application.cpp \
    Camera.cpp \
    Viewport.cpp \
    Source.cpp \
    Command.cpp \
    MainWindow.cpp \
    Properties.cpp \
    Options.cpp \
    RenderEngine.cpp \
    OctreeEditor.cpp

HEADERS  += \
    Application.h \
    Camera.h \
    Viewport.h \
    Source.h \
    Command.h \
    MainWindow.h \
    Properties.h \
    Options.h \
    RenderEngine.h \
    OctreeEditor.h \
    config.h

FORMS += \
    MainWindow.ui \
    Properties.ui

DISTFILES += \
    ../../data/shader/octreefarm/FrontLightOctree.frag \
    ../../data/shader/octreefarm/FrontLightOctree.vert

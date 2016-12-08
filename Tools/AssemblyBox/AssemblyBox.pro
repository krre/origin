QT += widgets
CONFIG += c++11
TARGET = AssemblyBox
TEMPLATE = app

win32: LIBS += -L$$(GLEW_HOME)/lib -lglew32 -lopengl32
linux: LIBS += -lGLEW

INCLUDEPATH += "../../ThirdParty" $$(GLEW_HOME)/include

SOURCES += main.cpp\
        MainWindow.cpp \
    Viewport.cpp \
    Properties.cpp

HEADERS  += MainWindow.h \
    Viewport.h \
    Properties.h

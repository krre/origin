QT += widgets
CONFIG += c++17
TARGET = AssemblyBox
TEMPLATE = app
DESTDIR = $$(ORIGIN_HOME)

SOURCES += main.cpp\
    MainWindow.cpp \
    Viewport.cpp \
    Properties.cpp

HEADERS += MainWindow.h \
    Viewport.h \
    Properties.h

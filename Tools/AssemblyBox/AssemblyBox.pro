QT += widgets
CONFIG += c++11
TARGET = AssemblyBox
TEMPLATE = app

SOURCES += main.cpp\
        MainWindow.cpp \
    Viewport.cpp \
    Properties.cpp

HEADERS  += MainWindow.h \
    Viewport.h \
    Properties.h

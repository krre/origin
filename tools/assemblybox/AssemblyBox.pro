QT += widgets
CONFIG += c++20
TARGET = AssemblyBox
TEMPLATE = app
DESTDIR = $$(ORIGIN_HOME)

SOURCES += main.cpp\
    MainWindow.cpp

HEADERS += \
    MainWindow.h \
    Defines.h

FORMS += \
    MainWindow.ui

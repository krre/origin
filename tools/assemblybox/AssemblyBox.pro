QT += widgets
CONFIG += c++20
TARGET = AssemblyBox
TEMPLATE = app
DESTDIR = $$(ORIGIN_HOME)

SOURCES += main.cpp\
    Application.cpp \
    MainWindow.cpp

HEADERS += \
    Application.h \
    MainWindow.h

FORMS += \
    MainWindow.ui

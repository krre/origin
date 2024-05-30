QT += widgets
CONFIG += c++20
TARGET = assemblybox
TEMPLATE = app
DESTDIR = $$(ORIGIN_HOME)

SOURCES += \
    main.cpp \
    Application.cpp \
    MainWindow.cpp

HEADERS += \
    Application.h \
    MainWindow.h

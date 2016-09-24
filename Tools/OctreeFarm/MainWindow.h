#pragma once
#include "GLWidget.h"
#include "ControlsWidget.h"
#include <QtWidgets>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = 0);
    ~MainWindow();

private slots:
    void newFile();
    void openFile();
    void saveFile();
    void saveAsFile();
    void closeFile();
    void about();

private:
    void setupMenuBar();

    QSplitter splitter;
    GLWidget* glWidget;
    ControlsWidget* controlsWidget;
};

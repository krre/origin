#pragma once
#include "Viewport.h"
#include "Properties.h"
#include "Octree.h"
#include <QtWidgets>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void newFile();
    void openFile();
    void saveFile();
    void saveAsFile();
    void about();

private:
    void setupMenuBar();
    void setupSplitter();
    void readSettings();
    void writeSettings();

    QSplitter* splitter;
    Viewport* viewport;
    Properties* properties;
    QSettings* settings;
    Octree octree;
    QString octreeFilePath;
    bool dirty = false;
};

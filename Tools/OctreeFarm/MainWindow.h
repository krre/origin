#pragma once
#include "Viewport.h"
#include "Properties.h"
#include "Octree.h"
#include <QMainWindow>
#include <QSplitter>
#include <QSettings>
#include <QCloseEvent>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void newFile();
    void open();
    bool save();
    bool saveAs();
    void about();
    void initViewport();

private:
    void setupMenuBar();
    void setupSplitter();
    void readSettings();
    void writeSettings();
    bool maybeSave();
    bool saveFile(const QString& fileName);

    QSplitter* splitter;
    Viewport* viewport;
    Properties* properties;
    QSettings* settings;
    Octree octree;
    QString octreeFilePath;
};

#pragma once
#include "Viewport.h"
#include "Properties.h"
#include "Octree.h"
#include <QMainWindow>
#include <QSplitter>
#include <QSettings>
#include <QCloseEvent>
#include <QFileDialog>
#include <QUndoStack>

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
    void revert();
    void about();
    void initViewport();
    void resetGeometry();
    void deleteNode();

private:
    void setupMenuBar();
    void setupActions();
    void setupSplitter();
    void readSettings();
    void writeSettings();
    bool maybeSave();
    bool saveFile(const QString& fileName);
    void loadFile(const QString& fileName);
    QString openFileDialog(QFileDialog::QFileDialog::AcceptMode mode);
    void setCurrentFile(const QString& fileName);

    QSplitter* splitter;
    Viewport* viewport;
    Properties* properties;
    QSettings* settings;
    Octree octree;
    QString currentFile;
    QUndoStack* undoStack;
};

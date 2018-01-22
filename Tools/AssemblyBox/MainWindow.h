#pragma once
#include "Viewport.h"
#include "Properties.h"
#include <QMainWindow>
#include <QSettings>
#include <QSplitter>

namespace AssemblyBox {

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = 0);

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void resetGeometry();
    void newPlanet();
    void about();

private:
    void setupMenuBar();
    void setupActions();
    void setupSplitter();
    void readSettings();
    void writeSettings();

    QSettings* settings;
    Viewport* viewport;
    Properties* properties;
    QSplitter splitter;
};

} // AssemblyBox

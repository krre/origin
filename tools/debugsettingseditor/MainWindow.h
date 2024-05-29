#pragma once
#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent* event);

private slots:
    // File
    void on_actionReload_triggered();

    // Help
    void on_actionAbout_triggered();


private:
    void readSettings();
    void writeSettings();

    void readDebugSettings();
    void writeDebugSettings();

    Ui::MainWindow* ui;
    QString debugSettingsPath;
};

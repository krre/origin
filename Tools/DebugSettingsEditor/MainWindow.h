#pragma once
#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent* event);

private slots:
    void on_actionAbout_triggered();
    void on_actionReload_triggered();

private:
    enum class Tabs {
        GENERAL,
        VULKAN
    };

    void readSettings();
    void writeSettings();

    void readDebugSettings();
    void writeDebugSettings();

    Ui::MainWindow* ui;
    QString settingsPath;
};

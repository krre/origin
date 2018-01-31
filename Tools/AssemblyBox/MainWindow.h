#pragma once
#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

namespace AssemblyBox {

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    // Help
    void on_actionAbout_triggered();

private:
    void readSettings();
    void writeSettings();

    Ui::MainWindow* ui;
    QString settingsPath;
};

} // AssemblyBox

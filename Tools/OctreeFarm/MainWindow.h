#pragma once
#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

namespace OctreeFarm {

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

private slots:
    void on_actionAbout_triggered();

private:
    Ui::MainWindow* ui;
};

} // OctreeFarm

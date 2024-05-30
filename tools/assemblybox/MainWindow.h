#pragma once
#include <QMainWindow>

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow();

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void about();

private:
    void createActions();

    void readSettings();
    void writeSettings();
};

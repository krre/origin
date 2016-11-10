#pragma once
#include <QMainWindow>
#include <QSettings>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = 0);

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void resetGeometry();
    void about();

private:
    void setupMenuBar();
    void setupActions();
    void readSettings();
    void writeSettings();

    QSettings* settings;
};

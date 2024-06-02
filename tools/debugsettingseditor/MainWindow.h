#pragma once
#include <QMainWindow>

class QTableWidget;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow();

protected:
    void closeEvent(QCloseEvent* event);

private slots:
    void reload();
    void about();

private:
    void createActions();

    void readSettings();
    void writeSettings();

    void readDebugSettings();
    void writeDebugSettings();

    QTabWidget* tabWidget = nullptr;
    QString debugSettingsPath;
};

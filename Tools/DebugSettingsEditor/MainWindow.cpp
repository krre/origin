#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Defines.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    settingsPath = QApplication::applicationDirPath() + "/" + APP_SETTINGS_NAME;
    readSettings();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent* event) {
    writeSettings();
    event->accept();
}

void MainWindow::readSettings() {
    QSettings settings(settingsPath, QSettings::IniFormat);
    settings.beginGroup("MainWindow");
    resize(settings.value("size", QSize(800, 600)).toSize());
    move(settings.value("pos", QPoint(200, 200)).toPoint());
    settings.endGroup();
}

void MainWindow::writeSettings() {
    QSettings settings(settingsPath, QSettings::IniFormat);
    settings.beginGroup("MainWindow");
    settings.setValue("size", size());
    settings.setValue("pos", pos());
    settings.endGroup();
}

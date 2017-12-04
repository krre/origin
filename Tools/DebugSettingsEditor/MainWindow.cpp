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

void MainWindow::on_actionAbout_triggered() {
    QMessageBox::about(this, tr("About %1").arg(APP_NAME),
        tr("<h3>%1 %2</h3> \
           Based on Qt %3<br> \
           Build on %4<br><br> \
           <a href=%5>%5</a><br><br> \
           Copyright © 2017, Vladimir Zarypov").
           arg(APP_NAME).arg(APP_VERSION_STR).arg(QT_VERSION_STR).arg(__DATE__).arg(APP_URL));
}

void MainWindow::readSettings() {
    QSettings settings(settingsPath, QSettings::IniFormat);
    settings.beginGroup("MainWindow");
    resize(settings.value("size", QSize(800, 600)).toSize());
    move(settings.value("pos", QPoint(200, 200)).toPoint());
    ui->tabWidget->setCurrentIndex(settings.value("tab", 0).toInt());
    settings.endGroup();
}

void MainWindow::writeSettings() {
    QSettings settings(settingsPath, QSettings::IniFormat);
    settings.beginGroup("MainWindow");
    settings.setValue("size", size());
    settings.setValue("pos", pos());
    settings.setValue("tab", ui->tabWidget->currentIndex());
    settings.endGroup();
}

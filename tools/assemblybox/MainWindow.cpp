#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Defines.h"
#include <QtWidgets>

MainWindow::MainWindow() : ui(new Ui::MainWindow) {
    setWindowTitle(APP_NAME);
    settingsPath = QApplication::applicationDirPath() + "/" + APP_SETTINGS_NAME;
    ui->setupUi(this);
    readSettings();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent* event) {
    writeSettings();
    QMainWindow::closeEvent(event);
}

void MainWindow::on_actionAbout_triggered() {
    QMessageBox::about(this, tr("About %1").arg(APP_NAME),
        tr("<h3>%1 %2</h3> \
           Universe editor for Origin game<br><br>\
           Based on Qt %3<br> \
           Build on %4<br><br> \
           <a href=%5>%5</a><br><br>%6").
           arg(APP_NAME).arg(APP_VERSION_STR).arg(QT_VERSION_STR).
            arg(__DATE__).arg(APP_URL).arg(APP_COPYRIGHT));
}

void MainWindow::readSettings() {
    QSettings settings(settingsPath, QSettings::IniFormat);
    settings.beginGroup("MainWindow");

    if (!restoreGeometry(settings.value("geometry").toByteArray())) {
        resize(WINDOW_WIDTH, WINDOW_HEIGHT);
        const QRect availableGeometry = QGuiApplication::screens().constFirst()->availableGeometry();
        move((availableGeometry.width() - width()) / 2, (availableGeometry.height() - height()) / 2);
    }

    settings.endGroup();
}

void MainWindow::writeSettings() {
    QSettings settings(settingsPath, QSettings::IniFormat);
    settings.beginGroup("MainWindow");
    settings.setValue("geometry", saveGeometry());
    settings.endGroup();
}

#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Defines.h"
#include <QtWidgets>

namespace OctreeFarm {

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setWindowTitle(APP_NAME);
    settings = new QSettings(QCoreApplication::applicationDirPath() + "/" + APP_SETTINGS_NAME, QSettings::IniFormat, this);
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
           <a href=%5>%5</a><br><br>%6").
           arg(APP_NAME).arg(APP_VERSION_STR).arg(QT_VERSION_STR).
           arg(__DATE__).arg(APP_URL).arg(APP_COPYRIGHT));
}

void MainWindow::readSettings() {
    settings->beginGroup("MainWindow");

    resize(settings->value("size", QSize(WINDOW_WIDTH, WINDOW_HEIGHT)).toSize());
    move(settings->value("pos", QPoint(WINDOW_X, WINDOW_Y)).toPoint());

    QVariant splitterSize = settings->value("splitter");
    if (splitterSize == QVariant()) {
        ui->splitter->setSizes({ 200, 500 });
    } else {
        ui->splitter->restoreState(splitterSize.toByteArray());
    }

    settings->endGroup();
}

void MainWindow::writeSettings() {
    settings->beginGroup("MainWindow");
    settings->setValue("size", size());
    settings->setValue("pos", pos());
    settings->setValue("splitter", ui->splitter->saveState());
    settings->endGroup();
}

} // OctreeFarm

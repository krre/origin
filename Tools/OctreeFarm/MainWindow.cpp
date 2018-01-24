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
}

MainWindow::~MainWindow() {
    delete ui;
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

} // OctreeFarm

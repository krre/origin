#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Defines.h"

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

} // OctreeFarm

#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    resize(800, 600);
}

MainWindow::~MainWindow() {
    delete ui;
}

#include "MainWindow.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    resetGeometry();
}

MainWindow::~MainWindow() {

}

void MainWindow::resetGeometry() {
    resize(800, 480);
    const QRect availableGeometry = QApplication::desktop()->availableGeometry(this);
    move((availableGeometry.width() - width()) / 2, (availableGeometry.height() - height()) / 2);
}

#include "MainWindow.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    resetGeometry();
    setupMenuBar();
}

void MainWindow::resetGeometry() {
    resize(800, 480);
    const QRect availableGeometry = QApplication::desktop()->availableGeometry(this);
    move((availableGeometry.width() - width()) / 2, (availableGeometry.height() - height()) / 2);
}

void MainWindow::setupMenuBar() {
    QMenu* fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(tr("Exit"), this, &QWidget::close, QKeySequence("Ctrl+Q"));

    QMenu* helpMenu = menuBar()->addMenu(tr("Help"));
    helpMenu->addAction(tr("About Qt..."), qApp, &QApplication::aboutQt);
}

#include "MainWindow.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    settings = new QSettings(QApplication::applicationDirPath() + "/" + QApplication::applicationName() + ".ini", QSettings::IniFormat);

    resetGeometry();
    setupMenuBar();
    setupActions();
    readSettings();
}

void MainWindow::closeEvent(QCloseEvent* event) {
    Q_UNUSED(event)
    writeSettings();
}

void MainWindow::resetGeometry() {
    resize(800, 480);
    const QRect availableGeometry = QApplication::desktop()->availableGeometry(this);
    move((availableGeometry.width() - width()) / 2, (availableGeometry.height() - height()) / 2);
}

void MainWindow::about() {
    QMessageBox::about(this, QString(tr("About %1")).arg(QApplication::applicationName()),
                       QString(tr("<h3><b>%1 %2<b></h3>"
                                  "Universe editor for Gagarin game<br>"
                                  "<a href=\"https://github.com/krre/gagarin\">"
                                  "https://github.com/krre/gagarin</a><br><br>"
                                  "Copyright © 2016, Vladimir Zarypov")).
                       arg(QApplication::applicationName()).arg(QApplication::applicationVersion()));
}

void MainWindow::setupMenuBar() {
    QMenu* fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(tr("Exit"), this, &QWidget::close, QKeySequence("Ctrl+Q"));

    QMenu* helpMenu = menuBar()->addMenu(tr("Help"));
    helpMenu->addAction(QString(tr("About %1...")).arg(QApplication::applicationName()), this, &MainWindow::about);
    helpMenu->addAction(tr("About Qt..."), qApp, &QApplication::aboutQt);
}

void MainWindow::setupActions() {
    QAction* resetGeometryAct = new QAction;
    resetGeometryAct->setShortcut(QKeySequence("Ctrl+F12"));
    connect(resetGeometryAct, &QAction::triggered, this, &MainWindow::resetGeometry);
    addAction(resetGeometryAct);
}

void MainWindow::readSettings() {
    const QByteArray geometry = settings->value("General/geometry", QByteArray()).toByteArray();
    if (geometry.isEmpty()) {
        resetGeometry();
    } else {
        restoreGeometry(geometry);
    }
}

void MainWindow::writeSettings() {
    settings->setValue("General/geometry", saveGeometry());
}

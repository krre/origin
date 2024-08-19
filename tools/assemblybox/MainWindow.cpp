#include "MainWindow.h"
#include "Application.h"
#include <QtWidgets>

MainWindow::MainWindow() {
    setWindowTitle(Application::Name);
    createActions();
    readSettings();
}

void MainWindow::closeEvent(QCloseEvent* event) {
    writeSettings();
    QMainWindow::closeEvent(event);
}

void MainWindow::about() {
    QMessageBox::about(this, tr("About %1").arg(Application::Name),
        tr("<h3>%1 %2</h3> \
           Universe editor for Origin game<br><br> \
           Based on Qt %3<br> \
           Build on %4 %5<br><br> \
           <a href=%6>%6</a><br><br>Copyright © %7, %8").
           arg(Application::Name, Application::Version, QT_VERSION_STR,
            Application::BuildDate, Application::BuildTime, Application::Url,
            Application::Years, Application::Author));
}

void MainWindow::createActions() {
    // File
    QMenu* fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(tr("Exit"), Qt::CTRL | Qt::Key_Q, this, &QMainWindow::close);

    // Help
    QMenu* helpMenu = menuBar()->addMenu(tr("Help"));
    helpMenu->addAction(tr("About %1...").arg(Application::Name), this, &MainWindow::about);
}

void MainWindow::readSettings() {
    QSettings settings;
    settings.beginGroup("MainWindow");

    if (!restoreGeometry(settings.value("geometry").toByteArray())) {
        resize(1200, 800);
        const QRect availableGeometry = QGuiApplication::screens().constFirst()->availableGeometry();
        move((availableGeometry.width() - width()) / 2, (availableGeometry.height() - height()) / 2);
    }

    settings.endGroup();
}

void MainWindow::writeSettings() {
    QSettings settings;
    settings.beginGroup("MainWindow");
    settings.setValue("geometry", saveGeometry());
    settings.endGroup();
}

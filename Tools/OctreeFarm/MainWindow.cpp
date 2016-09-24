#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    resize(800, 480);
    setWindowTitle(QApplication::applicationName());

    setupMenuBar();

    glWidget = new GLWidget;
    controlsWidget = new ControlsWidget;
    splitter.addWidget(controlsWidget);
    splitter.addWidget(glWidget);

    setCentralWidget(&splitter);
}

MainWindow::~MainWindow() {

}

void MainWindow::setupMenuBar() {
    QMenu* fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(tr("New File"), this, &MainWindow::newFile, QKeySequence("Ctrl+N"));
    fileMenu->addAction(tr("Open..."), this, &MainWindow::openFile, QKeySequence("Ctrl+O"));
    fileMenu->addAction(tr("Save"), this, &MainWindow::saveFile, QKeySequence("Ctrl+S"));
    fileMenu->addAction(tr("Save As..."), this, &MainWindow::saveAsFile, QKeySequence("Ctrl+Shift+S"));
    fileMenu->addAction(tr("Close"), this, &MainWindow::closeFile, QKeySequence("Ctrl+W"));
    fileMenu->addSeparator();
    fileMenu->addAction(tr("Exit"), this, &QWidget::close, QKeySequence("Ctrl+Q"));

    QMenu* helpMenu = menuBar()->addMenu(tr("Help"));
    helpMenu->addAction(QString(tr("About %1...")).arg(QApplication::applicationName()), this, &MainWindow::about);
    helpMenu->addAction(tr("About Qt..."), qApp, &QApplication::aboutQt);
}

void MainWindow::newFile() {
    qDebug() << "new";
}

void MainWindow::openFile() {

}

void MainWindow::saveFile() {

}

void MainWindow::saveAsFile() {

}

void MainWindow::closeFile() {

}

void MainWindow::about() {
    QMessageBox::about(this, QString(tr("About %1")).arg(QApplication::applicationName()),
            QString(tr("<h3><b>%1 %2<b></h3><br>Sparse voxel octree editor for Gagarin game")).arg(QApplication::applicationName()).arg(QApplication::applicationVersion()));
}

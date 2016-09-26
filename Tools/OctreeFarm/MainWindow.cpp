#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    resize(800, 480);
    setWindowTitle(QApplication::applicationName());

    setupMenuBar();
    setupSplitter();

    setCentralWidget(splitter);

    readSettings();
}

MainWindow::~MainWindow() {

}

void MainWindow::closeEvent(QCloseEvent* event) {
    writeSettings();
    event->accept();
}

void MainWindow::setupMenuBar() {
    QMenu* fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(tr("New"), this, &MainWindow::newFile, QKeySequence("Ctrl+N"));
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

void MainWindow::setupSplitter() {
    splitter = new QSplitter;
    splitter->setChildrenCollapsible(false);
    splitter->setFrameStyle(QFrame::Box | QFrame::Raised);
    splitter->setLineWidth(1);

    controlsWidget = new Properties;
    controlsWidget->setMinimumWidth(100);
    splitter->addWidget(controlsWidget);

    glWidget = new Viewport;
    glWidget->setMinimumWidth(100);
    splitter->addWidget(glWidget);

    QList<int> sizes;
    sizes << 250 << 550;
    splitter->setSizes(sizes);

    settings = new QSettings(QApplication::applicationDirPath() + "/" + QApplication::applicationName() + ".ini", QSettings::IniFormat);
}

void MainWindow::readSettings() {
    splitter->restoreState(settings->value("General/splitter").toByteArray());

    int x = settings->value("Window/x", 200).toInt();
    int y = settings->value("Window/y", 200).toInt();
    move(x, y);
}

void MainWindow::writeSettings() {
    settings->setValue("General/splitter", splitter->saveState());
    settings->setValue("Window/x", x());
    settings->setValue("Window/y", y());
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

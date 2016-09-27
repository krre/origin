#include "MainWindow.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    resize(800, 480);

    setupMenuBar();
    setupSplitter();

    setCentralWidget(splitter);

    readSettings();

    connect(viewport, &Viewport::ready, this, &MainWindow::initViewport);
    connect(&octree, &Octree::isModifiedChanged, this, &MainWindow::setWindowModified);

    setCurrentFile(QString());
}

MainWindow::~MainWindow() {

}

void MainWindow::closeEvent(QCloseEvent* event) {
    if (maybeSave()) {
        writeSettings();
        event->accept();
    } else {
        event->ignore();
    }
}

void MainWindow::setupMenuBar() {
    QMenu* fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(tr("New"), this, &MainWindow::newFile, QKeySequence("Ctrl+N"));
    fileMenu->addAction(tr("Open..."), this, &MainWindow::open, QKeySequence("Ctrl+O"));
    fileMenu->addAction(tr("Save"), this, &MainWindow::save, QKeySequence("Ctrl+S"));
    fileMenu->addAction(tr("Save As..."), this, &MainWindow::saveAs, QKeySequence("Ctrl+Shift+S"));
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

    properties = new Properties(&octree);
    properties->setMinimumWidth(100);
    splitter->addWidget(properties);

    viewport = new Viewport(&octree);
    viewport->setMinimumWidth(100);
    splitter->addWidget(viewport);

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

bool MainWindow::maybeSave() {
    if (!octree.isModified()) {
        return true;
    }

    const QMessageBox::StandardButton ret
        = QMessageBox::warning(this, QCoreApplication::applicationName(),
                               tr("The octree has been modified.\n"
                                  "Do you want to save your changes?"),
                               QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    switch (ret) {
    case QMessageBox::Save:
        return save();
    case QMessageBox::Cancel:
        return false;
    default:
        break;
    }
    return true;
}

bool MainWindow::saveFile(const QString& fileName) {
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, QCoreApplication::applicationName(),
                             tr("Cannot write file %1:\n%2.")
                             .arg(QDir::toNativeSeparators(fileName),
                                  file.errorString()));
        return false;
    }


#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(Qt::WaitCursor);
#endif

    octree.save(fileName);

#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif

    setCurrentFile(fileName);
    return true;
}

void MainWindow::setCurrentFile(const QString& fileName) {
    octreeFilePath = fileName;
    octree.setIsModified(false);
    setWindowModified(false);

    QString shownName = octreeFilePath;
    if (octreeFilePath.isEmpty()) {
        shownName = "untitled.octree";
    }
    setWindowFilePath(shownName);
    setWindowTitle(shownName + "[*] - " + QCoreApplication::applicationName());
}

void MainWindow::newFile() {
    if (maybeSave()) {
        octree.createNew();
        setCurrentFile(QString());
        viewport->updateOctreeInGPU(0, octree.data(), sizeof(uint32_t) * octree.count());
    }
}

void MainWindow::open() {
    octree.setIsModified(false);

}

bool MainWindow::save() {
    if (octreeFilePath.isEmpty()) {
        return saveAs();
    } else {
        return saveFile(octreeFilePath);
    }
}

bool MainWindow::saveAs() {
    QFileDialog dialog(this);
    dialog.setWindowModality(Qt::WindowModal);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    if (dialog.exec() != QDialog::Accepted) {
        return false;
    }
    return saveFile(dialog.selectedFiles().first());
}

void MainWindow::about() {
    QMessageBox::about(this, QString(tr("About %1")).arg(QApplication::applicationName()),
                       QString(tr("<h3><b>%1 %2<b></h3><br>Sparse voxel octree editor for Gagarin game")).arg(QApplication::applicationName()).arg(QApplication::applicationVersion()));
}

void MainWindow::initViewport() {
    newFile();
}

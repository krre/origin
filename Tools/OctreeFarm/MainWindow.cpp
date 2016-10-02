#include "MainWindow.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setupMenuBar();
    setupSplitter();
    setupActions();

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
    fileMenu->addAction(tr("Revert"), this, &MainWindow::revert);
    fileMenu->addSeparator();
    fileMenu->addAction(tr("Exit"), this, &QWidget::close, QKeySequence("Ctrl+Q"));

    QMenu* editMenu = menuBar()->addMenu(tr("Edit"));
    editMenu->addAction(tr("Undo"));
    editMenu->addAction(tr("Redo"));
    editMenu->addSeparator();

    QMenu* octreeMenu = menuBar()->addMenu(tr("Node"));
    octreeMenu->addAction(tr("Deselect"), &octree, &Octree::deselect);
    octreeMenu->addAction(tr("Split"), &octree, &Octree::splitNode, QKeySequence("S"));
    octreeMenu->addAction(tr("Merge"), &octree, &Octree::mergeNode, QKeySequence("M"));
    octreeMenu->addAction(tr("Add"), &octree, &Octree::addNode, QKeySequence("A"));
    octreeMenu->addAction(tr("Delete"), &octree, &Octree::deleteNode, QKeySequence("D"));

    QMenu* toolsMenu = menuBar()->addMenu(tr("Tools"));
    toolsMenu->addAction(tr("Options.."));

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

void MainWindow::setupSplitter() {
    splitter = new QSplitter;
    splitter->setChildrenCollapsible(false);

    // Properties
    QFrame* propFrame = new QFrame;
    propFrame->setFrameStyle(QFrame::Box | QFrame::Sunken);
    QBoxLayout* propLayout = new QBoxLayout(QBoxLayout::LeftToRight, propFrame);
    propLayout->setMargin(0);
    properties = new Properties(&octree);
    properties->setMinimumWidth(100);
    propLayout->addWidget(properties);
    splitter->addWidget(propFrame);

    // Viewport
    QFrame* viewportFrame = new QFrame;
    viewportFrame->setFrameStyle(QFrame::Box | QFrame::Sunken);
    QBoxLayout* viewportLayout = new QBoxLayout(QBoxLayout::LeftToRight, viewportFrame);
    viewportLayout->setMargin(0);
    viewport = new Viewport(&octree);
    viewport->setMinimumWidth(100);
    viewportLayout->addWidget(viewport);
    splitter->addWidget(viewportFrame);

    QList<int> sizes;
    sizes << 250 << 550;
    splitter->setSizes(sizes);

    settings = new QSettings(QApplication::applicationDirPath() + "/" + QApplication::applicationName() + ".ini", QSettings::IniFormat);
}

void MainWindow::resetGeometry() {
    resize(800, 480);
    const QRect availableGeometry = QApplication::desktop()->availableGeometry(this);
    move((availableGeometry.width() - width()) / 2, (availableGeometry.height() - height()) / 2);
}

void MainWindow::readSettings() {
    splitter->restoreState(settings->value("General/splitter").toByteArray());

    const QByteArray geometry = settings->value("General/geometry", QByteArray()).toByteArray();
    if (geometry.isEmpty()) {
        resetGeometry();
    } else {
        restoreGeometry(geometry);
    }
}

void MainWindow::writeSettings() {
    settings->setValue("General/splitter", splitter->saveState());
    settings->setValue("General/geometry", saveGeometry());
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

void MainWindow::loadFile(const QString& fileName) {
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, QCoreApplication::applicationName(),
                             tr("Cannot read file %1:\n%2.")
                             .arg(QDir::toNativeSeparators(fileName), file.errorString()));
        return;
    }

#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(Qt::WaitCursor);
#endif

    octree.load(fileName);

#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif

    setCurrentFile(fileName);
}

QString MainWindow::openFileDialog(QFileDialog::AcceptMode mode) {
    QFileDialog dialog(this);
    dialog.setWindowModality(Qt::WindowModal);
    dialog.setAcceptMode(mode);
    dialog.setNameFilter(tr("Octrees (*.octree)"));
    if (dialog.exec() != QDialog::Accepted) {
        return QString();
    }
    QString fileName = dialog.selectedFiles().first();
    QStringList list = fileName.split(".");
    if (list.length() > 0 && list.at(list.length() - 1) != "octree") {
        fileName += ".octree";
    }

    return fileName;
}

void MainWindow::setCurrentFile(const QString& fileName) {
    currentFile = fileName;
    octree.setIsModified(false);
    setWindowModified(false);

    QString shownName = QFileInfo(currentFile).fileName();
    if (currentFile.isEmpty()) {
        shownName = "untitled.octree";
    }
    setWindowFilePath(shownName);
    setWindowTitle(shownName + "[*] - " + QCoreApplication::applicationName());
}

void MainWindow::newFile() {
    if (maybeSave()) {
        octree.createNew();
        viewport->reset();
        viewport->updateOctreeInGPU(0, octree.data(), sizeof(uint32_t) * octree.count());
        viewport->update();
        setCurrentFile(QString());
    }
}

void MainWindow::open() {
    if (maybeSave()) {
        QString fileName = openFileDialog(QFileDialog::AcceptOpen);
        if (!fileName.isEmpty()) {
            loadFile(fileName);
            viewport->reset();
            viewport->updateOctreeInGPU(0, octree.data(), sizeof(uint32_t) * octree.count());
            viewport->update();
        }
    }
}

bool MainWindow::save() {
    if (currentFile.isEmpty()) {
        return saveAs();
    } else {
        return saveFile(currentFile);
    }
}

bool MainWindow::saveAs() {
    QString fileName = openFileDialog(QFileDialog::AcceptSave);
    if (!fileName.isEmpty()) {
        return saveFile(fileName);
    }

    return false;
}

void MainWindow::revert() {
    if (!currentFile.isEmpty()) {
        loadFile(currentFile);
        viewport->updateOctreeInGPU(0, octree.data(), sizeof(uint32_t) * octree.count());
        viewport->update();
    }
}

void MainWindow::about() {
    QMessageBox::about(this, QString(tr("About %1")).arg(QApplication::applicationName()),
                       QString(tr("<h3><b>%1 %2<b></h3>"
                                  "Sparse voxel octree editor for Gagarin game<br>"
                                  "<a href=\"https://github.com/krre/gagarin\">"
                                  "https://github.com/krre/gagarin</a><br><br>"
                                  "Copyright © 2016, Vladimir Zarypov")).
                       arg(QApplication::applicationName()).arg(QApplication::applicationVersion()));
}

void MainWindow::initViewport() {
    newFile();
}

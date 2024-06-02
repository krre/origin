#include "MainWindow.h"
#include "Application.h"
#include "OctreeEditor.h"
#include "Viewport.h"
#include "Properties.h"
#include "Command.h"
#include "Options.h"
#include <QtWidgets>

const int maxRecentFiles = 10;
const int separatorAndMenuCount = 2;
bool MainWindow::closing = false;

MainWindow::MainWindow() {
    setWindowTitle(Application::Name);

    undoStack = new QUndoStack(this);
    octreeEditor = new OctreeEditor(this);

    createActions();

    viewport = new Viewport(octreeEditor);
    connect(viewport, &Viewport::selectionChanged, this, &MainWindow::onSelectionChanged);
    QWidget* container = QWidget::createWindowContainer(viewport);

    properties = new Properties(octreeEditor, viewport, undoStack, this);

    splitter = new QSplitter(Qt::Horizontal);
    splitter->addWidget(container);
    splitter->addWidget(properties);

    setCentralWidget(splitter);

    readSettings();
    updateMenuState();

    connect(octreeEditor, &OctreeEditor::isModifiedChanged, this, &MainWindow::setWindowModified);
}

bool MainWindow::isClosing() {
    return closing;
}

void MainWindow::closeEvent(QCloseEvent* event) {
    closing = true;
    writeSettings();
    QMainWindow::closeEvent(event);
}

void MainWindow::create() {
    if (maybeSave()) {
        octreeEditor->createNew();
        viewport->reset();
        setCurrentFile(QString());
    }
}

void MainWindow::open() {
    if (maybeSave()) {
        QString fileName = openFileDialog(QFileDialog::AcceptOpen);
        if (!fileName.isEmpty()) {
            loadFile(fileName);
        }
    }
}

void MainWindow::revert() {
    if (!currentFile.isEmpty()) {
        loadFile(currentFile);
        viewport->update();
    }
}

void MainWindow::clearRecentMenu() {
    for (int i = recentFilesMenu->actions().size() - separatorAndMenuCount - 1; i >= 0; i--) {
        recentFilesMenu->removeAction(recentFilesMenu->actions().at(i));
    }

    updateMenuState();
}

void MainWindow::deselect() {
    viewport->deselect();
    octreeEditor->deselect();
}

void MainWindow::split() {
    QUndoCommand* splitCommand = new SplitCommand(octreeEditor);
    undoStack->push(splitCommand);
}

void MainWindow::merge() {
    QUndoCommand* addCommand = new AddCommand(octreeEditor, QGuiApplication::keyboardModifiers() == Qt::ShiftModifier);
    undoStack->push(addCommand);
}

void MainWindow::addForward() {
    QUndoCommand* mergeCommand = new MergeCommand(octreeEditor);
    undoStack->push(mergeCommand);
}

void MainWindow::addBack() {
    QUndoCommand* mergeCommand = new MergeCommand(octreeEditor);
    undoStack->push(mergeCommand);
}

void MainWindow::deleteNode() {
    QUndoCommand* deleteCommand = new DeleteCommand(octreeEditor);
    undoStack->push(deleteCommand);
}

void MainWindow::reset() {
    viewport->reset();
}

void MainWindow::options() {
    Options options;
    options.exec();
}

void MainWindow::about() {
    QMessageBox::about(this, tr("About %1").arg(Application::Name),
        tr("<h3>%1 %2</h3> \
           Octree editor for Origin game<br><br> \
           Based on Qt %3<br> \
           Build on %4 %5<br><br> \
           <a href=%6>%6</a><br><br>Copyright © %7, %8").
           arg(Application::Name, Application::Version, QT_VERSION_STR,
            Application::BuildDate, Application::BuildTime, Application::Url,
            Application::Years, Application::Author));
}

void MainWindow::onSelectionChanged(bool selected) {
    deselectAction->setEnabled(selected);
    splitAction->setEnabled(selected);
    mergeAction->setEnabled(selected);
    addForwardAction->setEnabled(selected);
    addBackAction->setEnabled(selected);
    deleteAction->setEnabled(selected);
}

void MainWindow::createActions() {
    auto fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(tr("New..."), Qt::CTRL | Qt::Key_N, this, &MainWindow::create);
    fileMenu->addAction(tr("Open..."), Qt::CTRL | Qt::Key_O, this, &MainWindow::open);
    fileMenu->addAction(tr("Save"), Qt::CTRL | Qt::Key_S, this, &MainWindow::save);
    fileMenu->addAction(tr("Save As..."), this, &MainWindow::saveAs);
    fileMenu->addAction(tr("Revert"), Qt::Key_F5, this, &MainWindow::revert);

    recentFilesMenu = new QMenu(tr("Recent Files"), fileMenu);
    recentFilesMenu->addSeparator();
    recentFilesMenu->addAction(tr("Clear"), this, &MainWindow::clearRecentMenu);


    fileMenu->addAction(recentFilesMenu->menuAction());
    fileMenu->addSeparator();
    fileMenu->addAction("Exit", Qt::CTRL | Qt::Key_Q, this, qOverload<>(&QMainWindow::close));

    auto editMenu = menuBar()->addMenu(tr("Edit"));
    editMenu->addAction(tr("Undo"), Qt::CTRL | Qt::Key_Z, undoStack, &QUndoStack::undo);
    editMenu->addAction(tr("Redo"), Qt::CTRL | Qt::SHIFT | Qt::Key_Z, undoStack, &QUndoStack::redo);
    editMenu->addSeparator();
    editMenu->addAction(tr("Copy"), Qt::CTRL | Qt::Key_C, octreeEditor, &OctreeEditor::copy);
    editMenu->addAction(tr("Paste"), Qt::CTRL | Qt::Key_V, octreeEditor, &OctreeEditor::paste);

    auto nodeMenu = menuBar()->addMenu(tr("Node"));
    deselectAction = nodeMenu->addAction(tr("Deselect"), this, &MainWindow::deselect);
    splitAction = nodeMenu->addAction(tr("Split"), Qt::Key_S, this, &MainWindow::split);
    mergeAction = nodeMenu->addAction(tr("Merge"), Qt::Key_M, this, &MainWindow::merge);
    addForwardAction = nodeMenu->addAction(tr("Add Forward"), Qt::Key_A, this, &MainWindow::addForward);
    addBackAction = nodeMenu->addAction(tr("Add Back"), Qt::SHIFT | Qt::Key_A, this, &MainWindow::addBack);
    deleteAction = nodeMenu->addAction(tr("Delete"), Qt::Key_D, this, &MainWindow::deleteNode);

    auto viewMenu = menuBar()->addMenu(tr("View"));
    viewMenu->addAction(tr("Reset"), Qt::CTRL | Qt::Key_F12, this, &MainWindow::reset);

    auto toolsMenu = menuBar()->addMenu(tr("Tools"));
    toolsMenu->addAction(tr("Options..."), this, &MainWindow::options);

    auto helpMenu = menuBar()->addMenu(tr("Help"));
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

    QVariant splitterSize = settings.value("splitter");
    if (splitterSize == QVariant()) {
        splitter->setSizes({ 500, 150 });
    } else {
        splitter->restoreState(splitterSize.toByteArray());
    }

    properties->setShadeless(settings.value("shadeless").toBool());

    settings.endGroup();

    int size = settings.beginReadArray("RecentFiles");
    for (int i = 0; i < size; ++i) {
        settings.setArrayIndex(i);
        addRecentFile(settings.value("path").toString());
    }
    settings.endArray();

    QString filePath = settings.value("Path/currentFile").toString();
    if (!filePath.isEmpty() && QFile::exists(filePath)) {
        loadFile(filePath);
    } else {
        create();
    }
}

void MainWindow::writeSettings() {
    QSettings settings;
    settings.beginGroup("MainWindow");
    settings.setValue("geometry", saveGeometry());
    settings.setValue("splitter", splitter->saveState());
    settings.setValue("shadeless", properties->shadeless());
    settings.endGroup();

    settings.setValue("Path/currentFile", currentFile);

    settings.beginWriteArray("RecentFiles");
    for (int i = 0; i <recentFilesMenu->actions().size() - separatorAndMenuCount; ++i) {
        settings.setArrayIndex(i);
        settings.setValue("path", recentFilesMenu->actions().at(i)->text());
    }
    settings.endArray();
}

bool MainWindow::maybeSave() {
    if (!octreeEditor->isModified()) {
        return true;
    }

    const QMessageBox::StandardButton button = QMessageBox::warning(this, QCoreApplication::applicationName(),
                               tr("The octree has been modified.\n"
                                  "Do you want to save your changes?"),
                               QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    switch (button) {
        case QMessageBox::Save:
            return save();
        case QMessageBox::Cancel:
            return false;
        default:
            break;
    }

    return true;
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

    octreeEditor->save(fileName);

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

    octreeEditor->load(fileName);

#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif

    viewport->reset();
    setCurrentFile(fileName);
    addRecentFile(fileName);
}

QString MainWindow::openFileDialog(QFileDialog::AcceptMode mode) {
    QFileDialog dialog(this);
    dialog.setWindowModality(Qt::WindowModal);
    dialog.setAcceptMode(mode);
    dialog.setNameFilter(tr("JSON Octrees (*.json)"));
    if (dialog.exec() != QDialog::Accepted) {
        return QString();
    }
    QString fileName = dialog.selectedFiles().first();
    QStringList list = fileName.split(".");
    if (list.length() > 0 && list.at(list.length() - 1) != "json") {
        fileName += ".json";
    }

    return fileName;
}

void MainWindow::setCurrentFile(const QString& fileName) {
    currentFile = fileName;
    octreeEditor->setModified(false);
    setWindowModified(false);

    QString shownName = QFileInfo(currentFile).fileName();
    if (currentFile.isEmpty()) {
        shownName = "untitled.json";
    }
    setWindowFilePath(shownName);
    setWindowTitle(shownName + "[*] - " + QCoreApplication::applicationName());
}

void MainWindow::addRecentFile(const QString& filePath) {
    QMenu* menu = recentFilesMenu;

    for (QAction* action : menu->actions()) {
        if (action->text() == filePath) {
            menu->removeAction(action);
        }
    }

    QAction* fileAction = new QAction(filePath);
    connect(fileAction, &QAction::triggered, [=] {
        loadFile(filePath);
    });
    menu->insertAction(menu->actions().first(), fileAction);

    if (menu->actions().size() > maxRecentFiles + separatorAndMenuCount) {
        menu->removeAction(menu->actions().at(menu->actions().size() - separatorAndMenuCount - 1));
    }

    updateMenuState();
}

void MainWindow::updateMenuState() {
    recentFilesMenu->menuAction()->setEnabled(recentFilesMenu->actions().size() > separatorAndMenuCount);
}

#include "MainWindow.h"
#include "Application.h"
#include "OctreeEditor.h"
#include "Viewport.h"
#include "Properties.h"
#include "Command.h"
#include "Options.h"
#include <QSplitter>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QSettings>
#include <QScreen>

const int maxRecentFiles = 10;
const int separatorAndMenuCount = 2;
bool MainWindow::s_closing = false;

MainWindow::MainWindow() {
    setWindowTitle(Application::Name);

    m_undoStack = new QUndoStack(this);
    m_octreeEditor = new OctreeEditor(this);

    createActions();

    m_viewport = new Viewport(m_octreeEditor);
    connect(m_viewport, &Viewport::selectionChanged, this, &MainWindow::onSelectionChanged);
    QWidget* container = QWidget::createWindowContainer(m_viewport);

    m_properties = new Properties(m_octreeEditor, m_viewport, m_undoStack, this);

    m_splitter = new QSplitter(Qt::Horizontal);
    m_splitter->addWidget(container);
    m_splitter->addWidget(m_properties);

    setCentralWidget(m_splitter);

    readSettings();
    updateMenuState();

    connect(m_octreeEditor, &OctreeEditor::isModifiedChanged, this, &MainWindow::setWindowModified);
}

bool MainWindow::isClosing() {
    return s_closing;
}

void MainWindow::closeEvent(QCloseEvent* event) {
    s_closing = true;
    writeSettings();

    QMainWindow::closeEvent(event);
}

void MainWindow::create() {
    if (maybeSave()) {
        m_octreeEditor->createNew();
        m_viewport->reset();
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
    if (!m_currentFile.isEmpty()) {
        loadFile(m_currentFile);
        m_viewport->update();
    }
}

void MainWindow::clearRecentMenu() {
    for (int i = m_recentFilesMenu->actions().size() - separatorAndMenuCount - 1; i >= 0; i--) {
        m_recentFilesMenu->removeAction(m_recentFilesMenu->actions().at(i));
    }

    updateMenuState();
}

void MainWindow::deselect() {
    m_viewport->deselect();
    m_octreeEditor->deselect();
}

void MainWindow::split() {
    QUndoCommand* splitCommand = new SplitCommand(m_octreeEditor);
    m_undoStack->push(splitCommand);
}

void MainWindow::merge() {
    QUndoCommand* addCommand = new AddCommand(m_octreeEditor, QGuiApplication::keyboardModifiers() == Qt::ShiftModifier);
    m_undoStack->push(addCommand);
}

void MainWindow::addForward() {
    QUndoCommand* mergeCommand = new MergeCommand(m_octreeEditor);
    m_undoStack->push(mergeCommand);
}

void MainWindow::addBack() {
    QUndoCommand* mergeCommand = new MergeCommand(m_octreeEditor);
    m_undoStack->push(mergeCommand);
}

void MainWindow::deleteNode() {
    QUndoCommand* deleteCommand = new DeleteCommand(m_octreeEditor);
    m_undoStack->push(deleteCommand);
}

void MainWindow::reset() {
    m_viewport->reset();
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
    m_deselectAction->setEnabled(selected);
    m_splitAction->setEnabled(selected);
    m_mergeAction->setEnabled(selected);
    m_addForwardAction->setEnabled(selected);
    m_addBackAction->setEnabled(selected);
    m_deleteAction->setEnabled(selected);
}

void MainWindow::createActions() {
    auto fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(tr("New..."), Qt::CTRL | Qt::Key_N, this, &MainWindow::create);
    fileMenu->addAction(tr("Open..."), Qt::CTRL | Qt::Key_O, this, &MainWindow::open);
    fileMenu->addAction(tr("Save"), Qt::CTRL | Qt::Key_S, this, &MainWindow::save);
    fileMenu->addAction(tr("Save As..."), this, &MainWindow::saveAs);
    fileMenu->addAction(tr("Revert"), Qt::Key_F5, this, &MainWindow::revert);

    m_recentFilesMenu = new QMenu(tr("Recent Files"), fileMenu);
    m_recentFilesMenu->addSeparator();
    m_recentFilesMenu->addAction(tr("Clear"), this, &MainWindow::clearRecentMenu);


    fileMenu->addAction(m_recentFilesMenu->menuAction());
    fileMenu->addSeparator();
    fileMenu->addAction("Exit", Qt::CTRL | Qt::Key_Q, this, qOverload<>(&QMainWindow::close));

    auto editMenu = menuBar()->addMenu(tr("Edit"));
    editMenu->addAction(tr("Undo"), Qt::CTRL | Qt::Key_Z, m_undoStack, &QUndoStack::undo);
    editMenu->addAction(tr("Redo"), Qt::CTRL | Qt::SHIFT | Qt::Key_Z, m_undoStack, &QUndoStack::redo);
    editMenu->addSeparator();
    editMenu->addAction(tr("Copy"), Qt::CTRL | Qt::Key_C, m_octreeEditor, &OctreeEditor::copy);
    editMenu->addAction(tr("Paste"), Qt::CTRL | Qt::Key_V, m_octreeEditor, &OctreeEditor::paste);

    auto nodeMenu = menuBar()->addMenu(tr("Node"));
    m_deselectAction = nodeMenu->addAction(tr("Deselect"), this, &MainWindow::deselect);
    m_splitAction = nodeMenu->addAction(tr("Split"), Qt::Key_S, this, &MainWindow::split);
    m_mergeAction = nodeMenu->addAction(tr("Merge"), Qt::Key_M, this, &MainWindow::merge);
    m_addForwardAction = nodeMenu->addAction(tr("Add Forward"), Qt::Key_A, this, &MainWindow::addForward);
    m_addBackAction = nodeMenu->addAction(tr("Add Back"), Qt::SHIFT | Qt::Key_A, this, &MainWindow::addBack);
    m_deleteAction = nodeMenu->addAction(tr("Delete"), Qt::Key_D, this, &MainWindow::deleteNode);

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
        m_splitter->setSizes({ 500, 150 });
    } else {
        m_splitter->restoreState(splitterSize.toByteArray());
    }

    m_properties->setShadeless(settings.value("shadeless").toBool());

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
    settings.setValue("splitter", m_splitter->saveState());
    settings.setValue("shadeless", m_properties->shadeless());
    settings.endGroup();

    settings.setValue("Path/currentFile", m_currentFile);

    settings.beginWriteArray("RecentFiles");

    for (int i = 0; i <m_recentFilesMenu->actions().size() - separatorAndMenuCount; ++i) {
        settings.setArrayIndex(i);
        settings.setValue("path", m_recentFilesMenu->actions().at(i)->text());
    }

    settings.endArray();
}

bool MainWindow::maybeSave() {
    if (!m_octreeEditor->isModified()) {
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
    if (m_currentFile.isEmpty()) {
        return saveAs();
    } else {
        return saveFile(m_currentFile);
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

    m_octreeEditor->save(fileName);

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

    m_octreeEditor->load(fileName);

#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif

    m_viewport->reset();
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
    m_currentFile = fileName;
    m_octreeEditor->setModified(false);
    setWindowModified(false);

    QString shownName = QFileInfo(m_currentFile).fileName();

    if (m_currentFile.isEmpty()) {
        shownName = "untitled.json";
    }

    setWindowFilePath(shownName);
    setWindowTitle(shownName + "[*] - " + QCoreApplication::applicationName());
}

void MainWindow::addRecentFile(const QString& filePath) {
    QMenu* menu = m_recentFilesMenu;

    for (QAction* action : menu->actions()) {
        if (action->text() == filePath) {
            menu->removeAction(action);
        }
    }

    QAction* fileAction = new QAction(filePath);

    connect(fileAction, &QAction::triggered, this, [=, this] {
        loadFile(filePath);
    });

    menu->insertAction(menu->actions().first(), fileAction);

    if (menu->actions().size() > maxRecentFiles + separatorAndMenuCount) {
        menu->removeAction(menu->actions().at(menu->actions().size() - separatorAndMenuCount - 1));
    }

    updateMenuState();
}

void MainWindow::updateMenuState() {
    m_recentFilesMenu->menuAction()->setEnabled(m_recentFilesMenu->actions().size() > separatorAndMenuCount);
}

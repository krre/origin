#include "MainWindow.h"
#include "Application.h"
#include "ui_MainWindow.h"
#include "OctreeEditor.h"
#include "Viewport.h"
#include "Properties.h"
#include "Command.h"
#include "Options.h"
#include <QtWidgets>

const int maxRecentFiles = 10;
const int separatorAndMenuCount = 2;
bool MainWindow::closing = false;

MainWindow::MainWindow() : ui(new Ui::MainWindow) {
    setWindowTitle(Application::Name);
    ui->setupUi(this);

    undoStack = new QUndoStack(this);
    octreeEditor = new OctreeEditor(this);

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

MainWindow::~MainWindow() {
    delete ui;
}

bool MainWindow::isClosing() {
    return closing;
}

void MainWindow::closeEvent(QCloseEvent* event) {
    closing = true;
    writeSettings();
    QMainWindow::closeEvent(event);
}

void MainWindow::on_actionNew_triggered() {
    if (maybeSave()) {
        octreeEditor->createNew();
        viewport->reset();
        setCurrentFile(QString());
    }
}

void MainWindow::on_actionOpen_triggered() {
    if (maybeSave()) {
        QString fileName = openFileDialog(QFileDialog::AcceptOpen);
        if (!fileName.isEmpty()) {
            loadFile(fileName);
        }
    }
}

void MainWindow::on_actionSave_triggered() {
    save();
}

void MainWindow::on_actionSaveAs_triggered() {
    saveAs();
}

void MainWindow::on_actionRevert_triggered() {
    if (!currentFile.isEmpty()) {
        loadFile(currentFile);
        viewport->update();
    }
}

void MainWindow::on_actionClearMenuRecentFiles_triggered() {
    QMenu* menu = ui->menuRecentFiles;
    for (int i = menu->actions().size() - separatorAndMenuCount - 1; i >= 0; i--) {
        menu->removeAction(menu->actions().at(i));
    }

    updateMenuState();
}

void MainWindow::on_actionUndo_triggered() {
    undoStack->undo();
}

void MainWindow::on_actionRedo_triggered() {
    undoStack->redo();
}

void MainWindow::on_actionCopy_triggered() {
    octreeEditor->copy();
}

void MainWindow::on_actionPaste_triggered() {
    octreeEditor->paste();
}

void MainWindow::on_actionDeselect_triggered() {
    viewport->deselect();
    octreeEditor->deselect();
}

void MainWindow::on_actionSplit_triggered() {
    QUndoCommand* splitCommand = new SplitCommand(octreeEditor);
    undoStack->push(splitCommand);
}

void MainWindow::on_actionMerge_triggered() {
    QUndoCommand* addCommand = new AddCommand(octreeEditor, QGuiApplication::keyboardModifiers() == Qt::ShiftModifier);
    undoStack->push(addCommand);
}

void MainWindow::on_actionAddForward_triggered() {
    QUndoCommand* mergeCommand = new MergeCommand(octreeEditor);
    undoStack->push(mergeCommand);
}

void MainWindow::on_actionAddBack_triggered() {
    QUndoCommand* mergeCommand = new MergeCommand(octreeEditor);
    undoStack->push(mergeCommand);
}

void MainWindow::on_actionDelete_triggered() {
    QUndoCommand* deleteCommand = new DeleteCommand(octreeEditor);
    undoStack->push(deleteCommand);
}

void MainWindow::on_actionReset_triggered() {
    viewport->reset();
}

void MainWindow::on_actionOptions_triggered() {
    Options options;
    options.exec();
}

void MainWindow::on_actionAbout_triggered() {
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
    ui->actionDeselect->setEnabled(selected);
    ui->actionSplit->setEnabled(selected);
    ui->actionMerge->setEnabled(selected);
    ui->actionAddBack->setEnabled(selected);
    ui->actionAddForward->setEnabled(selected);
    ui->actionDelete->setEnabled(selected);
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
        on_actionNew_triggered();
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
    for (int i = 0; i < ui->menuRecentFiles->actions().size() - separatorAndMenuCount; ++i) {
        settings.setArrayIndex(i);
        settings.setValue("path", ui->menuRecentFiles->actions().at(i)->text());
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
    QMenu* menu = ui->menuRecentFiles;

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
    ui->menuRecentFiles->menuAction()->setEnabled(ui->menuRecentFiles->actions().size() > separatorAndMenuCount);
}

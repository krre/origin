#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Defines.h"
#include "OctreeEditor.h"
#include "Viewport.h"
#include "Properties.h"
#include "Command.h"
#include "Options.h"
#include "Settings.h"
#include <QtWidgets>

namespace OctreeFarm {

MainWindow::MainWindow(QWidget* parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow) {
    ui->setupUi(this);

    undoStack = new QUndoStack(this);
    octree = new OctreeEditor(this);

    viewport = new Viewport;
    QWidget* container = QWidget::createWindowContainer(viewport);
    QBoxLayout* viewportlayout = new QBoxLayout(QBoxLayout::TopToBottom, ui->frameViewport);
    viewportlayout->setMargin(0);
    viewportlayout->addWidget(container);

    QBoxLayout* propLayout = new QBoxLayout(QBoxLayout::LeftToRight, ui->frameProperties);
    propLayout->setMargin(0);
    properties = new Properties(octree, viewport, undoStack, this);
    propLayout->addWidget(properties);

    setWindowTitle(APP_NAME);

    readSettings();

    connect(octree, &OctreeEditor::isModifiedChanged, this, &MainWindow::setWindowModified);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent* event) {
    writeSettings();
    QMainWindow::closeEvent(event);
}

void MainWindow::on_actionNew_triggered() {
    if (maybeSave()) {
        octree->createNew();
        viewport->reset();
        setCurrentFile(QString());
    }
}

void MainWindow::on_actionOpen_triggered() {
    if (maybeSave()) {
        QString fileName = openFileDialog(QFileDialog::AcceptOpen);
        if (!fileName.isEmpty()) {
            loadFile(fileName);
            viewport->reset();
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

void MainWindow::on_actionUndo_triggered() {
    undoStack->undo();
}

void MainWindow::on_actionRedo_triggered() {
    undoStack->redo();
}

void MainWindow::on_actionCopy_triggered() {
    octree->copy();
}

void MainWindow::on_actionPaste_triggered() {
    octree->paste();
}

void MainWindow::on_actionDeselect_triggered() {
    octree->deselect();
}

void MainWindow::on_actionSplit_triggered() {
    QUndoCommand* splitCommand = new SplitCommand(octree);
    undoStack->push(splitCommand);
}

void MainWindow::on_actionMerge_triggered() {
    QUndoCommand* addCommand = new AddCommand(octree, QGuiApplication::keyboardModifiers() == Qt::ShiftModifier);
    undoStack->push(addCommand);
}

void MainWindow::on_actionAddForward_triggered() {
    QUndoCommand* mergeCommand = new MergeCommand(octree);
    undoStack->push(mergeCommand);
}

void MainWindow::on_actionAddBack_triggered() {
    QUndoCommand* mergeCommand = new MergeCommand(octree);
    undoStack->push(mergeCommand);
}

void MainWindow::on_actionDelete_triggered() {
    QUndoCommand* deleteCommand = new DeleteCommand(octree);
    undoStack->push(deleteCommand);
}

void MainWindow::on_actionOptions_triggered() {
    Options options(this);
    options.exec();
}

void MainWindow::on_actionAbout_triggered() {
    QMessageBox::about(this, tr("About %1").arg(APP_NAME),
        tr("<h3>%1 %2</h3> \
           Octree editor for Origin game<br><br>\
           Based on Qt %3<br> \
           Build on %4<br><br> \
           <a href=%5>%5</a><br><br>%6").
           arg(APP_NAME).arg(APP_VERSION_STR).arg(QT_VERSION_STR).
           arg(__DATE__).arg(APP_URL).arg(APP_COPYRIGHT));
}

void MainWindow::readSettings() {
    Settings::beginGroup("MainWindow");

    if (!restoreGeometry(Settings::getValue("geometry").toByteArray())) {
        resize(WINDOW_WIDTH, WINDOW_HEIGHT);
        const QRect availableGeometry = QApplication::desktop()->availableGeometry(this);
        move((availableGeometry.width() - width()) / 2, (availableGeometry.height() - height()) / 2);
    }

    QVariant splitterSize = Settings::getValue("splitter");
    if (splitterSize == QVariant()) {
        ui->splitter->setSizes({ 500, 150 });
    } else {
        ui->splitter->restoreState(splitterSize.toByteArray());
    }

    Settings::endGroup();

    QString filePath = Settings::getValue("Path/currentFile").toString();
    if (!filePath.isEmpty() && QFile::exists(filePath)) {
        loadFile(filePath);
    } else {
        on_actionNew_triggered();
    }
}

void MainWindow::writeSettings() {
    Settings::beginGroup("MainWindow");
    Settings::setValue("geometry", saveGeometry());
    Settings::setValue("splitter", ui->splitter->saveState());
    Settings::endGroup();

    Settings::setValue("Path/currentFile", currentFile);
}

bool MainWindow::maybeSave() {
    if (!octree->getIsModified()) {
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

    octree->save(fileName);

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

    octree->load(fileName);

#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif

    setCurrentFile(fileName);
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
    octree->setIsModified(false);
    setWindowModified(false);

    QString shownName = QFileInfo(currentFile).fileName();
    if (currentFile.isEmpty()) {
        shownName = "untitled.json";
    }
    setWindowFilePath(shownName);
    setWindowTitle(shownName + "[*] - " + QCoreApplication::applicationName());
}

} // OctreeFarm

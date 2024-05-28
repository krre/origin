#pragma once
#include <QMainWindow>
#include <QFileDialog>

namespace Ui {
    class MainWindow;
}

class QUndoStack;

class Properties;
class Viewport;
class OctreeEditor;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

    static bool isClosing();

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    // File
    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionSaveAs_triggered();
    void on_actionRevert_triggered();
    void on_actionClearMenuRecentFiles_triggered();

    // Edit
    void on_actionUndo_triggered();
    void on_actionRedo_triggered();
    void on_actionCopy_triggered();
    void on_actionPaste_triggered();

    // Node
    void on_actionDeselect_triggered();
    void on_actionSplit_triggered();
    void on_actionMerge_triggered();
    void on_actionAddForward_triggered();
    void on_actionAddBack_triggered();
    void on_actionDelete_triggered();

    // View
    void on_actionReset_triggered();

    // Tools
    void on_actionOptions_triggered();

    // Help
    void on_actionAbout_triggered();

    // Viewport
    void onSelectionChanged(bool selected);

private:
    void readSettings();
    void writeSettings();

    bool save();
    bool saveAs();

    bool maybeSave();
    bool saveFile(const QString& fileName);
    void loadFile(const QString& fileName);
    QString openFileDialog(QFileDialog::QFileDialog::AcceptMode mode);
    void setCurrentFile(const QString& fileName);
    void addRecentFile(const QString& filePath);
    void updateMenuState();

    Ui::MainWindow* ui;
    Properties* properties;
    Viewport* viewport;
    OctreeEditor* octreeEditor;
    QString currentFile;
    QUndoStack* undoStack;
    static bool closing;

};

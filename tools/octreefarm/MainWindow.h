#pragma once
#include <QMainWindow>
#include <QFileDialog>

class QUndoStack;
class QSplitter;

class Properties;
class Viewport;
class OctreeEditor;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow();

    static bool isClosing();

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    // File
    void create();
    void open();
    bool save();
    bool saveAs();
    void revert();

    void clearRecentMenu();

    // Node
    void deselect();
    void split();
    void merge();
    void addForward();
    void addBack();
    void deleteNode();

    // View
    void reset();

    // Tools
    void options();

    // Help
    void about();

    // Viewport
    void onSelectionChanged(bool selected);

private:
    void createActions();

    void readSettings();
    void writeSettings();

    bool maybeSave();
    bool saveFile(const QString& fileName);
    void loadFile(const QString& fileName);
    QString openFileDialog(QFileDialog::QFileDialog::AcceptMode mode);
    void setCurrentFile(const QString& fileName);
    void addRecentFile(const QString& filePath);
    void updateMenuState();

    QMenu* recentFilesMenu = nullptr;

    QAction* deselectAction = nullptr;
    QAction* splitAction = nullptr;
    QAction* mergeAction = nullptr;
    QAction* addForwardAction = nullptr;
    QAction* addBackAction = nullptr;
    QAction* deleteAction = nullptr;

    Properties* properties;
    Viewport* viewport;
    OctreeEditor* octreeEditor;
    QString currentFile;
    QSplitter* splitter = nullptr;
    QUndoStack* undoStack;
    static bool closing;

};

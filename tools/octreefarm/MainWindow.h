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
    void preferences();

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

    QMenu* m_recentFilesMenu = nullptr;

    QAction* m_deselectAction = nullptr;
    QAction* m_splitAction = nullptr;
    QAction* m_mergeAction = nullptr;
    QAction* m_addForwardAction = nullptr;
    QAction* m_addBackAction = nullptr;
    QAction* m_deleteAction = nullptr;

    Properties* m_properties;
    Viewport* m_viewport;
    OctreeEditor* m_octreeEditor = nullptr;
    QString m_currentFile;
    QSplitter* m_splitter = nullptr;
    QUndoStack* m_undoStack;
    static bool s_closing;

};

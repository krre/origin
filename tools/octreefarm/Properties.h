#pragma once
#include <QWidget>

class QUndoStack;
class QLabel;
class QPushButton;
class QCheckBox;

class OctreeEditor;
class Viewport;

class Properties : public QWidget {
    Q_OBJECT
public:
    Properties(OctreeEditor* octree, Viewport* viewport, QUndoStack* undoStack, QWidget* parent = nullptr);

    void setNodeLevel(int level);
    void setNodeIndex(int index);
    void setNodeColor(const QColor& color);

    void setShadeless(bool shadeless);
    bool shadeless() const;

private slots:
    void changeNodeColor();
    void onNodeSelected(int level, int index, const QColor& color);
    void onNodeDeselected();

    void levelPlus();
    void levelMinus();
    void levelReset();

private:
    void createUi();

    OctreeEditor* octree;
    Viewport* viewport;
    QUndoStack* undoStack;
    QColor nodeColor;

    QLabel* levelLabel = nullptr;
    QLabel* indexLabel = nullptr;
    QPushButton* colorButton = nullptr;
    QCheckBox* shadelessCheckBox = nullptr;
};

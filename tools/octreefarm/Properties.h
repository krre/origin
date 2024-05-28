#pragma once
#include <QWidget>

namespace Ui {
    class Properties;
}

class QUndoStack;

class OctreeEditor;
class Viewport;

class Properties : public QWidget {
    Q_OBJECT

public:
    explicit Properties(OctreeEditor* octree, Viewport* viewport, QUndoStack* undoStack, QWidget* parent = 0);
    ~Properties();
    void setNodeLevel(int level);
    void setNodeIndex(int index);
    void setNodeColor(const QColor& color);

    void setShadeless(bool shadeless);
    bool getShadeless() const;

private slots:
    void changeNodeColor();
    void onNodeSelected(int level, int index, const QColor& color);
    void onNodeDeselected();

    void levelPlus();
    void levelMinus();
    void levelReset();

private:
    Ui::Properties *ui;
    OctreeEditor* octree;
    Viewport* viewport;
    QUndoStack* undoStack;
    QColor nodeColor;
};

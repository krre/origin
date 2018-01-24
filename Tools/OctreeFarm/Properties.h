#pragma once
#include <QWidget>

namespace Ui {
    class Properties;
}

class QUndoStack;

namespace OctreeFarm {

class Octree;
class Viewport;

class Properties : public QWidget {
    Q_OBJECT

public:
    explicit Properties(Octree* octree, Viewport* viewport, QUndoStack* undoStack, QWidget* parent = 0);
    ~Properties();
    void setNodeLevel(int level);
    void setNodeIndex(int index);
    void setNodeColor(const QColor& color);

private slots:
    void changeNodeColor();
    void onNodeSelected(int level, int index, const QColor& color);
    void onNodeDeselected();

    void levelPlus();
    void levelMinus();
    void levelReset();

private:
    Ui::Properties *ui;
    Octree* octree;
    Viewport* viewport;
    QUndoStack* undoStack;
    QColor nodeColor;
};

} // OctreeFarm

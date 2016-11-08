#pragma once
#include "Viewport.h"
#include "Octree.h"
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QUndoStack>

class Properties : public QWidget {
    Q_OBJECT

public:
    explicit Properties(Octree* octree, Viewport* viewport, QUndoStack* undoStack);
    void setNodeLevel(int level);
    void setNodeIndex(int index);
    void setNodeColor(const QColor& color);

private slots:
    void changeNodeColor();
    void onNodeSelected(int level, int index, const QColor& color);
    void onNodeDeselected();
    void levelPlus();

private:
    Octree* octree;
    Viewport* viewport;
    QUndoStack* undoStack;
    QColor nodeColor;
    QPushButton* colorButton;
    QLabel* levelLabel;
    QLabel* indexLabel;
};

#pragma once
#include "Viewport.h"
#include "Octree.h"
#include <QWidget>
#include <QPushButton>
#include <QLabel>

class Properties : public QWidget {
    Q_OBJECT

public:
    explicit Properties(Octree* octree, Viewport* viewport);
    void setNodeLevel(int level);
    void setNodeIndex(int index);
    void setNodeColor(const QColor& color);

private slots:
    void changeNodeColor();
    void onNodeSelected(int level, int index, const QColor& color);
    void onNodeDeselected();

private:
    Octree* octree;
    Viewport* viewport;
    QColor nodeColor;
    QPushButton* colorButton;
    QLabel* levelLabel;
    QLabel* indexLabel;
};

#pragma once
#include "Octree.h"
#include "Viewport.h"
#include <QWidget>
#include <QPushButton>
#include <QLabel>

class Properties : public QWidget {
    Q_OBJECT

public:
    explicit Properties(Octree* octree, Viewport* viewport);
    void setNodeIndex(int index);
    void setNodeColor(const QColor& color);

private slots:
    void changeNodeColor();
    void onNodeSelected(int index, const QColor& color);
    void onNodeDeselected();

private:
    Octree* octree;
    Viewport* viewport;
    QColor nodeColor;
    QPushButton* colorButton;
    QLabel* indexLabel;
};

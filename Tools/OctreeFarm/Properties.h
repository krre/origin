#pragma once
#include "Octree.h"
#include <QWidget>
#include <QPushButton>

class Properties : public QWidget {
    Q_OBJECT

public:
    explicit Properties(Octree* octree);

private slots:
    void changeNodeColor();

private:
    Octree* octree;
    QColor nodeColor;
    QPalette colorButtonPal;
    QPushButton* colorButton;
};

#pragma once
#include "Octree.h"
#include <QWidget>

class Properties : public QWidget {
    Q_OBJECT

public:
    explicit Properties(Octree* octree);

private:
    Octree* octree;
};

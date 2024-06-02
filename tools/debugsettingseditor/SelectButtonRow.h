#pragma once
#include <QHBoxLayout>

class SelectButtonRow : public QHBoxLayout {
    Q_OBJECT
public:
    SelectButtonRow();

signals:
    void select();
    void unselect();
    void reset();
};

#pragma once
#include <QObject>
#include <QVector>
#include <cstdint>

class Octree : public QObject {
    Q_OBJECT

public:
    explicit Octree(QObject* parent = 0);
    uint32_t* data() { return storage.data(); }
    int count() { return storage.size(); }

private:
    QVector<uint32_t> storage;
};

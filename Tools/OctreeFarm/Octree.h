#pragma once
#include <QObject>
#include <QVector>
#include <cstdint>
#include <glm/ext.hpp>

class Octree : public QObject {
    Q_OBJECT

public:
    explicit Octree(QObject* parent = 0);

    uint32_t* data() { return storage.data(); }
    int count() { return storage.size(); }

    glm::mat4 octreeToWorld() const { return m_octreeToWorld; }
    glm::mat4 worldToOctree() const { return m_worldToOctree; }

private:
    QVector<uint32_t> storage;
    glm::mat4 m_octreeToWorld = glm::mat4(1.0);
    glm::mat4 m_worldToOctree = glm::mat4(1.0);
};

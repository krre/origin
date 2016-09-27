#pragma once
#include <QtCore>
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

    void createNew();
    void createTest();
    void save(const QString& filePath);

private:
    QVector<uint32_t> storage;
    uint32_t defaultColor = 0x7E4681FF;
    glm::mat4 m_octreeToWorld = glm::mat4(1.0);
    glm::mat4 m_worldToOctree = glm::mat4(1.0);
};

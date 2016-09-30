#pragma once
#include <cstdint>
#include <glm/ext.hpp>
#include <QObject>
#include "../../Source/Core/Common.h"
#include <QVector>

struct Node {
    uint32_t parent;
    uint32_t childIndex;
    uint32_t color;
};

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
    bool save(const QString& fileName);
    bool load(const QString& fileName);

    void setIsModified(bool isModified);
    bool isModified() const { return m_isModified; }

    QVector<Node>& selection() { return m_selection; }
    void select(Node node, bool append = false);

public slots:
    void deselect();

signals:
    void isModifiedChanged(bool isModified);
    void dataChanged();

private:
    int bitCount8(int value);

    QVector<uint32_t> storage;
    QVector<Node> m_selection;
    uint32_t defaultColor = 0x7E4681FF;
    glm::mat4 m_octreeToWorld = glm::mat4(1.0);
    glm::mat4 m_worldToOctree = glm::mat4(1.0);
    bool m_isModified = false;
};

#pragma once
#include <QObject> // Must be before Common.h since need define QT_VERSION macro
#include "../../Source/Core/Common.h"
#include "Source.h"
#include <QVector>
#include <QSharedPointer>
#include <glm/ext.hpp>

struct Node {
    uint32_t parent;
    uint32_t childIndex;
    uint32_t color;
    glm::vec3 pos;
};

class Octree : public QObject {
    Q_OBJECT

public:
    explicit Octree(QObject* parent = 0);

    uint32_t* data() { return storage->data(); }
    int count() { return storage->size(); }

    glm::mat4 octreeToWorld() const { return m_octreeToWorld; }
    glm::mat4 worldToOctree() const { return m_worldToOctree; }

    void createNew();
    void createTest();
    bool save(const QString& fileName);
    bool load(const QString& fileName);

    void setIsModified(bool isModified);
    bool isModified() const { return m_isModified; }

    void select(uint32_t parent, uint32_t childIndex, const glm::vec3& pos, bool append = false);
    void changeNodeColor(const QColor& color);

public slots:
    void deselect();
    void splitNode();
    void mergeNode();
    void addNode();
    void deleteNode();

signals:
    void isModifiedChanged(bool isModified);
    void nodeSelected(int index, const QColor& color);
    void nodeDeselected();
    void dataChanged();

private:
    int colorAttachAddress(int parent, int childIndex);

    Source source;
    QSharedPointer<QVector<uint32_t>> storage;
    QVector<QSharedPointer<Node>> m_selection;
    uint32_t selectionColor = 0xFF909090;
    glm::mat4 m_octreeToWorld = glm::mat4(1.0);
    glm::mat4 m_worldToOctree = glm::mat4(1.0);
    bool m_isModified = false;
};

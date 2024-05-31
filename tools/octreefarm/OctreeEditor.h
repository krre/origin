#pragma once
#include <QObject> // Must be before Common.h since need define QT_VERSION macro
#include <core/Common.h>
#include <octree/Octree.h>
#include <QVector>
#include <QColor>
#include <QSharedPointer>
#include <glm/ext.hpp>

namespace Octree {
    class Octree;
}

class Source;

struct Node {
    uint32_t parent;
    uint32_t childIndex;
    uint32_t color;
    uint32_t scale;
    glm::vec3 pos;
};

struct Clipboard {
    QColor color;
};

class OctreeEditor : public QObject {
    Q_OBJECT
public:
    OctreeEditor(QObject* parent = nullptr);
    ~OctreeEditor();

    uint32_t* data() { return storage->data(); }
    int count() { return storage->size(); }

    glm::mat4 octreeToWorld() const { return m_octreeToWorld; }
    glm::mat4 worldToOctree() const { return m_worldToOctree; }

    void createNew();
    void split(const Octree::Octree::Path& path = Octree::Octree::Path());
    bool save(const QString& fileName);
    bool load(const QString& fileName);
    void confirmUpdate();

    void setModified(bool modified);
    bool isModified() const { return m_modified; }

    void select(uint32_t parent, uint32_t scale, uint32_t childIndex, const glm::vec3& pos, bool append = false);

    QVector<QSharedPointer<Node>> selection() { return m_selection; }
    Source* source() { return m_source; }
    Octree::Octree* octree() const { return m_octree.data(); }

public slots:
    void deselect();
    void copy();
    void paste();

signals:
    void isModifiedChanged(bool isModified);
    void nodeSelected(int level, int index, const QColor& color);
    void nodeDeselected();
    void dataChanged();

private:
    int colorAttachOffset(int parent, int childIndex);

    QScopedPointer<Octree::Octree> m_octree;
    Source* m_source;
    QSharedPointer<QVector<uint32_t>> storage;
    QVector<QSharedPointer<Node>> m_selection;
    uint32_t selectionColor = 0xFF909090;
    glm::mat4 m_octreeToWorld = glm::mat4(1.0);
    glm::mat4 m_worldToOctree = glm::mat4(1.0);
    bool m_modified = false;
    Clipboard clipboard;
};

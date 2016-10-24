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
    uint32_t scale;
    glm::vec3 pos;
};

struct Clipboard {
    QColor color;
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
    bool save(const QString& fileName);
    bool load(const QString& fileName);

    void setIsModified(bool isModified);
    bool getIsModified() const { return isModified; }

    void select(uint32_t parent, uint32_t scale, uint32_t childIndex, const glm::vec3& pos, bool append = false);
    void changeNodeColor(const QColor& color);

public slots:
    void deselect();
    void splitNode();
    void mergeNode();
    void addNode();
    void deleteNode();
    void copy();
    void paste();

signals:
    void isModifiedChanged(bool isModified);
    void nodeSelected(int level, int index, const QColor& color);
    void nodeDeselected();
    void dataChanged();

private:
    int colorAttachOffset(int parent, int childIndex);
    void confirmUpdate();

    Source source;
    QSharedPointer<QVector<uint32_t>> storage;
    QVector<QSharedPointer<Node>> selection;
    uint32_t selectionColor = 0xFF909090;
    glm::mat4 m_octreeToWorld = glm::mat4(1.0);
    glm::mat4 m_worldToOctree = glm::mat4(1.0);
    bool isModified = false;
    Clipboard clipboard;
};

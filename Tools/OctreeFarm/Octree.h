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
    void confirmUpdate();

    void setIsModified(bool modified);
    bool isModified() const { return modified; }

    void select(uint32_t parent, uint32_t scale, uint32_t childIndex, const glm::vec3& pos, bool append = false);

    QVector<QSharedPointer<Node>> getSelection() { return selection; }
    Source* getSource() { return &source; }

public slots:
    void deselect();
    void copy();
    void paste();

signals:
    void isModifiedChanged(bool modified);
    void nodeSelected(int level, int index, const QColor& color);
    void nodeDeselected();
    void dataChanged();

private:
    int colorAttachOffset(int parent, int childIndex);

    Source source;
    QSharedPointer<QVector<uint32_t>> storage;
    QVector<QSharedPointer<Node>> selection;
    uint32_t selectionColor = 0xFF909090;
    glm::mat4 m_octreeToWorld = glm::mat4(1.0);
    glm::mat4 m_worldToOctree = glm::mat4(1.0);
    bool modified = false;
    Clipboard clipboard;
};

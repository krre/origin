#pragma once
#include <QObject> // Must be before Common.h since need define QT_VERSION macro
#include "Core/Common.h"
#include <QVector>
#include <QColor>
#include <QSharedPointer>
#include <glm/ext.hpp>

namespace OctreeFarm {

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
    explicit OctreeEditor(QObject* parent = 0);

    uint32_t* data() { return storage->data(); }
    int count() { return storage->size(); }

    glm::mat4 getOctreeToWorld() const { return octreeToWorld; }
    glm::mat4 getWorldToOctree() const { return worldToOctree; }

    void createNew();
    bool save(const QString& fileName);
    bool load(const QString& fileName);
    void confirmUpdate();

    void setIsModified(bool isModified);
    bool getIsModified() const { return isModified; }

    void select(uint32_t parent, uint32_t scale, uint32_t childIndex, const glm::vec3& pos, bool append = false);

    QVector<QSharedPointer<Node>> getSelection() { return selection; }
    Source* getSource() { return source; }

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

    Source* source;
    QSharedPointer<QVector<uint32_t>> storage;
    QVector<QSharedPointer<Node>> selection;
    uint32_t selectionColor = 0xFF909090;
    glm::mat4 octreeToWorld = glm::mat4(1.0);
    glm::mat4 worldToOctree = glm::mat4(1.0);
    bool isModified = false;
    Clipboard clipboard;
};

} // OctreeFarm

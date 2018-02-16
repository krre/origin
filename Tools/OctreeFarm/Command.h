#pragma once
#include "OctreeEditor.h"
#include <QUndoCommand>

namespace OctreeFarm {

class DeleteCommand : public QUndoCommand {

public:
    explicit DeleteCommand(OctreeEditor* octree);
    void undo() override;
    void redo() override;

private:
    OctreeEditor* octree;
    QVector<QSharedPointer<Node>> nodes;
};

class AddCommand : public QUndoCommand {

public:
    explicit AddCommand(OctreeEditor* octree, bool back = false);
    void undo() override;
    void redo() override;

private:
    OctreeEditor* octree;
    bool back;
    QVector<QSharedPointer<Node>> nodes;
    Node node;
};

class SplitCommand : public QUndoCommand {

public:
    explicit SplitCommand(OctreeEditor* octree);
    void undo() override;
    void redo() override;

private:
    OctreeEditor* octree;
    QVector<QSharedPointer<Node>> nodes;
};

class MergeCommand : public QUndoCommand {

public:
    explicit MergeCommand(OctreeEditor* octree);
    void undo() override;
    void redo() override;

private:
    OctreeEditor* octree;
    QVector<QSharedPointer<Node>> nodes;
    QVector<Node> mergedNodes;
    Node newNode;
};

class ChangeColorCommand : public QUndoCommand {

public:
    explicit ChangeColorCommand(OctreeEditor* octree, QColor color);
    void undo() override;
    void redo() override;

private:
    OctreeEditor* octree;
    QVector<QSharedPointer<Node>> nodes;
    QColor color;
};

} // OctreeFarm

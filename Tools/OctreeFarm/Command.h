#pragma once
#include "Octree.h"
#include <QUndoCommand>

class DeleteCommand : public QUndoCommand {

public:
    explicit DeleteCommand(Octree* octree);
    void undo() override;
    void redo() override;

private:
    Octree* octree;
    QVector<QSharedPointer<Node>> nodes;
};

class AddCommand : public QUndoCommand {

public:
    explicit AddCommand(Octree* octree, bool back = false);
    void undo() override;
    void redo() override;

private:
    Octree* octree;
    bool back;
    QVector<QSharedPointer<Node>> nodes;
    Node node;
};

class SplitCommand : public QUndoCommand {

public:
    explicit SplitCommand(Octree* octree);
    void undo() override;
    void redo() override;

private:
    Octree* octree;
    QVector<QSharedPointer<Node>> nodes;
};

class MergeCommand : public QUndoCommand {

public:
    explicit MergeCommand(Octree* octree);
    void undo() override;
    void redo() override;

private:
    Octree* octree;
    QVector<QSharedPointer<Node>> nodes;
};

class ChangeColorCommand : public QUndoCommand {

public:
    explicit ChangeColorCommand(Octree* octree, QColor color);
    void undo() override;
    void redo() override;

private:
    Octree* octree;
    QVector<QSharedPointer<Node>> nodes;
    QColor color;
};

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
    explicit AddCommand(QUndoCommand* parent = 0);
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

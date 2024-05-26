#pragma once
#include "OctreeEditor.h"
#include <QUndoCommand>

class DeleteCommand : public QUndoCommand {

public:
    explicit DeleteCommand(OctreeEditor* octreeEditor);
    void undo() override;
    void redo() override;

private:
    OctreeEditor* octreeEditor;
    QVector<QSharedPointer<Node>> nodes;
};

class AddCommand : public QUndoCommand {

public:
    explicit AddCommand(OctreeEditor* octreeEditor, bool back = false);
    void undo() override;
    void redo() override;

private:
    OctreeEditor* octreeEditor;
    bool back;
    QVector<QSharedPointer<Node>> nodes;
    Node node;
};

class SplitCommand : public QUndoCommand {

public:
    explicit SplitCommand(OctreeEditor* octreeEditor);
    void undo() override;
    void redo() override;

private:
    OctreeEditor* octreeEditor;
    QVector<QSharedPointer<Node>> nodes;
};

class MergeCommand : public QUndoCommand {

public:
    explicit MergeCommand(OctreeEditor* octreeEditor);
    void undo() override;
    void redo() override;

private:
    OctreeEditor* octreeEditor;
    QVector<QSharedPointer<Node>> nodes;
    QVector<Node> mergedNodes;
    Node newNode;
};

class ChangeColorCommand : public QUndoCommand {

public:
    explicit ChangeColorCommand(OctreeEditor* octreeEditor, QColor color);
    void undo() override;
    void redo() override;

private:
    OctreeEditor* octreeEditor;
    QVector<QSharedPointer<Node>> nodes;
    QColor color;
};

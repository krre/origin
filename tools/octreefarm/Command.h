#pragma once
#include "OctreeEditor.h"
#include <QUndoCommand>

class DeleteCommand : public QUndoCommand {

public:
    explicit DeleteCommand(OctreeEditor* octreeEditor);
    void undo() override;
    void redo() override;

private:
    OctreeEditor* m_octreeEditor;
    QVector<QSharedPointer<Node>> m_nodes;
};

class AddCommand : public QUndoCommand {

public:
    explicit AddCommand(OctreeEditor* octreeEditor, bool back = false);
    void undo() override;
    void redo() override;

private:
    OctreeEditor* m_octreeEditor;
    bool m_back;
    QVector<QSharedPointer<Node>> m_nodes;
    Node m_node;
};

class SplitCommand : public QUndoCommand {

public:
    explicit SplitCommand(OctreeEditor* octreeEditor);
    void undo() override;
    void redo() override;

private:
    OctreeEditor* m_octreeEditor;
    QVector<QSharedPointer<Node>> m_nodes;
};

class MergeCommand : public QUndoCommand {

public:
    explicit MergeCommand(OctreeEditor* octreeEditor);
    void undo() override;
    void redo() override;

private:
    OctreeEditor* m_octreeEditor;
    QVector<QSharedPointer<Node>> m_nodes;
    QVector<Node> m_mergedNodes;
    Node m_newNode;
};

class ChangeColorCommand : public QUndoCommand {

public:
    explicit ChangeColorCommand(OctreeEditor* octreeEditor, QColor color);
    void undo() override;
    void redo() override;

private:
    OctreeEditor* m_octreeEditor;
    QVector<QSharedPointer<Node>> m_nodes;
    QColor m_color;
};

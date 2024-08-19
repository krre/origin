#include "Command.h"
#include "Source.h"
#include <QtCore>

DeleteCommand::DeleteCommand(OctreeEditor* octreeEditor) : m_octreeEditor(octreeEditor) {
    m_nodes = octreeEditor->selection();
}

void DeleteCommand::undo() {
    bool result = false;
    for (auto node: m_nodes) {
        result = m_octreeEditor->source()->addNode(*node.data());
    }

    if (result) {
        m_octreeEditor->confirmUpdate();
    } else {
        qDebug() << "Failure add node";
    }
}

void DeleteCommand::redo() {
    if (m_octreeEditor->source()->deleteNode(m_nodes)) {
        m_octreeEditor->confirmUpdate();
    } else {
        qDebug() << "Failure delete node";
    }
}

AddCommand::AddCommand(OctreeEditor* octreeEditor, bool back) : m_octreeEditor(octreeEditor), m_back(back) {
    m_nodes = octreeEditor->selection();
}

void AddCommand::undo() {
    if (m_octreeEditor->source()->deleteNode(m_node)) {
        m_octreeEditor->confirmUpdate();
    } else {
        qDebug() << "Failure delete node";
    }
}

void AddCommand::redo() {
    if (m_octreeEditor->source()->addNode(m_nodes, m_back, m_node)) {
        m_octreeEditor->confirmUpdate();
    } else {
        qDebug() << "Failure add node";
    }
}

SplitCommand::SplitCommand(OctreeEditor* octreeEditor) : m_octreeEditor(octreeEditor) {
    m_nodes = octreeEditor->selection();
}

void SplitCommand::undo() {
    bool result = false;
    for (auto node: m_nodes) {
        result = m_octreeEditor->source()->mergeNode(*node.data());
    }
    if (result) {
        m_octreeEditor->confirmUpdate();
    } else {
        qDebug() << "Failure merge node";
    }
}

void SplitCommand::redo() {
    m_octreeEditor->split();
    m_octreeEditor->confirmUpdate();
}

MergeCommand::MergeCommand(OctreeEditor* octreeEditor) : m_octreeEditor(octreeEditor) {
    m_nodes = octreeEditor->selection();
}

void MergeCommand::undo() {
    m_octreeEditor->source()->createChildren(m_newNode);
    bool result = false;
    for (auto node: m_mergedNodes) {
        result = m_octreeEditor->source()->addNode(node);
    }
    if (result) {
        m_octreeEditor->confirmUpdate();
    } else {
        qDebug() << "Failure merge node";
    }
}

void MergeCommand::redo() {
    if (m_octreeEditor->source()->mergeNode(m_nodes, m_newNode, m_mergedNodes)) {
        m_octreeEditor->confirmUpdate();
    } else {
        qDebug() << "Failure merge node";
    }
}

ChangeColorCommand::ChangeColorCommand(OctreeEditor* octreeEditor, QColor color) : m_octreeEditor(octreeEditor), m_color(color) {
    m_nodes = octreeEditor->selection();
}

void ChangeColorCommand::undo() {
    bool result = false;
    for (auto node: m_nodes) {
        result = m_octreeEditor->source()->changeNodeColor(*node.data());
    }
    if (result) {
        m_octreeEditor->confirmUpdate();
    } else {
        qDebug() << "Failure change node color";
    }
}

void ChangeColorCommand::redo() {
    if (m_octreeEditor->source()->changeNodeColor(m_nodes, m_color)) {
        m_octreeEditor->confirmUpdate();
    } else {
        qDebug() << "Failure change node color";
    }
}

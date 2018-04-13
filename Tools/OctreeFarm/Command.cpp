#include "Command.h"
#include "Source.h"
#include <QtCore>

namespace OctreeFarm {

DeleteCommand::DeleteCommand(OctreeEditor* octreeEditor) : octreeEditor(octreeEditor) {
    nodes = octreeEditor->getSelection();
}

void DeleteCommand::undo() {
    bool result = false;
    for (auto node: nodes) {
        result = octreeEditor->getSource()->addNode(*node.data());
    }

    if (result) {
        octreeEditor->confirmUpdate();
    } else {
        qDebug() << "Failure add node";
    }
}

void DeleteCommand::redo() {
    if (octreeEditor->getSource()->deleteNode(nodes)) {
        octreeEditor->confirmUpdate();
    } else {
        qDebug() << "Failure delete node";
    }
}

AddCommand::AddCommand(OctreeEditor* octreeEditor, bool back) : octreeEditor(octreeEditor), back(back) {
    nodes = octreeEditor->getSelection();
}

void AddCommand::undo() {
    if (octreeEditor->getSource()->deleteNode(node)) {
        octreeEditor->confirmUpdate();
    } else {
        qDebug() << "Failure delete node";
    }
}

void AddCommand::redo() {
    if (octreeEditor->getSource()->addNode(nodes, back, node)) {
        octreeEditor->confirmUpdate();
    } else {
        qDebug() << "Failure add node";
    }
}

SplitCommand::SplitCommand(OctreeEditor* octreeEditor) : octreeEditor(octreeEditor) {
    nodes = octreeEditor->getSelection();
}

void SplitCommand::undo() {
    bool result = false;
    for (auto node: nodes) {
        result = octreeEditor->getSource()->mergeNode(*node.data());
    }
    if (result) {
        octreeEditor->confirmUpdate();
    } else {
        qDebug() << "Failure merge node";
    }
}

void SplitCommand::redo() {
    if (octreeEditor->getSource()->splitNode(nodes)) {
        octreeEditor->confirmUpdate();
    } else {
        qDebug() << "Failure split node";
    }
}

MergeCommand::MergeCommand(OctreeEditor* octreeEditor) : octreeEditor(octreeEditor) {
    nodes = octreeEditor->getSelection();
}

void MergeCommand::undo() {
    octreeEditor->getSource()->createChildren(newNode);
    bool result = false;
    for (auto node: mergedNodes) {
        result = octreeEditor->getSource()->addNode(node);
    }
    if (result) {
        octreeEditor->confirmUpdate();
    } else {
        qDebug() << "Failure merge node";
    }
}

void MergeCommand::redo() {
    if (octreeEditor->getSource()->mergeNode(nodes, newNode, mergedNodes)) {
        octreeEditor->confirmUpdate();
    } else {
        qDebug() << "Failure merge node";
    }
}

ChangeColorCommand::ChangeColorCommand(OctreeEditor* octreeEditor, QColor color) : octreeEditor(octreeEditor), color(color) {
    nodes = octreeEditor->getSelection();
}

void ChangeColorCommand::undo() {
    bool result = false;
    for (auto node: nodes) {
        result = octreeEditor->getSource()->changeNodeColor(*node.data());
    }
    if (result) {
        octreeEditor->confirmUpdate();
    } else {
        qDebug() << "Failure change node color";
    }
}

void ChangeColorCommand::redo() {
    if (octreeEditor->getSource()->changeNodeColor(nodes, color)) {
        octreeEditor->confirmUpdate();
    } else {
        qDebug() << "Failure change node color";
    }
}

} // OctreeFarm

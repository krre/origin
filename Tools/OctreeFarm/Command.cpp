#include "Command.h"
#include <QtCore>

DeleteCommand::DeleteCommand(Octree* octree) : octree(octree) {
    nodes = octree->getSelection();
}

void DeleteCommand::undo() {
    bool result = false;
    for (auto node: nodes) {
        result = octree->getSource()->addNode(*node.data());
    }

    if (result) {
        octree->confirmUpdate();
    } else {
        qDebug() << "Failure add node";
    }
}

void DeleteCommand::redo() {
    if (octree->getSource()->deleteNode(nodes)) {
        octree->confirmUpdate();
    } else {
        qDebug() << "Failure delete node";
    }
}

AddCommand::AddCommand(Octree* octree, bool back) : octree(octree), back(back) {
    nodes = octree->getSelection();
}

void AddCommand::undo() {
    if (octree->getSource()->deleteNode(node)) {
        octree->confirmUpdate();
    } else {
        qDebug() << "Failure delete node";
    }
}

void AddCommand::redo() {
    if (octree->getSource()->addNode(nodes, back, node)) {
        octree->confirmUpdate();
    } else {
        qDebug() << "Failure add node";
    }
}

SplitCommand::SplitCommand(Octree* octree) : octree(octree) {
    nodes = octree->getSelection();
}

void SplitCommand::undo() {
    bool result = false;
    for (auto node: nodes) {
        result = octree->getSource()->mergeNode(*node.data());
    }
    if (result) {
        octree->confirmUpdate();
    } else {
        qDebug() << "Failure merge node";
    }
}

void SplitCommand::redo() {
    if (octree->getSource()->splitNode(nodes)) {
        octree->confirmUpdate();
    } else {
        qDebug() << "Failure split node";
    }
}

MergeCommand::MergeCommand(Octree* octree) : octree(octree) {
    nodes = octree->getSelection();
}

void MergeCommand::undo() {
    octree->getSource()->createChildren(newNode);
    bool result = false;
    for (auto node: mergedNodes) {
        result = octree->getSource()->addNode(node);
    }
    if (result) {
        octree->confirmUpdate();
    } else {
        qDebug() << "Failure merge node";
    }
}

void MergeCommand::redo() {
    if (octree->getSource()->mergeNode(nodes, newNode, mergedNodes)) {
        octree->confirmUpdate();
    } else {
        qDebug() << "Failure merge node";
    }
}

ChangeColorCommand::ChangeColorCommand(Octree* octree, QColor color) : octree(octree), color(color) {
    nodes = octree->getSelection();
}

void ChangeColorCommand::undo() {
    bool result = false;
    for (auto node: nodes) {
        result = octree->getSource()->changeNodeColor(node);
    }
    if (result) {
        octree->confirmUpdate();
    } else {
        qDebug() << "Failure change node color";
    }
}

void ChangeColorCommand::redo() {
    if (octree->getSource()->changeNodeColor(nodes, color)) {
        octree->confirmUpdate();
    } else {
        qDebug() << "Failure change node color";
    }
}

#include "Command.h"
#include <QtCore>

DeleteCommand::DeleteCommand(Octree* octree) : octree(octree) {
    nodes = octree->getSelection();
}

void DeleteCommand::undo() {
    bool result = false;
    for (auto node: nodes) {
        result = octree->getSource()->addNode(node);
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

AddCommand::AddCommand(QUndoCommand* parent) : QUndoCommand(parent) {

}

SplitCommand::SplitCommand(Octree* octree) : octree(octree) {
    nodes = octree->getSelection();
}

void SplitCommand::undo() {
    bool result = false;
    for (auto node: nodes) {
        result = octree->getSource()->mergeNode(node);
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

ChangeColorCommand::ChangeColorCommand(Octree* octree, QColor color) : octree(octree), color(color) {
    nodes = octree->getSelection();
}

void ChangeColorCommand::undo() {
//    bool result = false;
//    for (auto node: nodes) {
//        result = octree->getSource()->mergeNode(node);
//    }
//    if (result) {
//        octree->confirmUpdate();
//    } else {
//        qDebug() << "Failure merge node";
//    }
}

void ChangeColorCommand::redo() {
    if (octree->getSource()->changeNodeColor(nodes, color)) {
        octree->confirmUpdate();
    } else {
        qDebug() << "Failure change node color";
    }
}

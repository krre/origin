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

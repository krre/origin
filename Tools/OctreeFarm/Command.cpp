#include "Command.h"
#include <QtCore>

DeleteCommand::DeleteCommand(Octree* octree) : octree(octree) {
    nodes = octree->getSelection();
}

void DeleteCommand::undo() {
    if (octree->getSource()->addNode(nodes)) {
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

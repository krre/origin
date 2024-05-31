#include "Command.h"
#include "Source.h"
#include <QtCore>

DeleteCommand::DeleteCommand(OctreeEditor* octreeEditor) : octreeEditor(octreeEditor) {
    nodes = octreeEditor->selection();
}

void DeleteCommand::undo() {
    bool result = false;
    for (auto node: nodes) {
        result = octreeEditor->source()->addNode(*node.data());
    }

    if (result) {
        octreeEditor->confirmUpdate();
    } else {
        qDebug() << "Failure add node";
    }
}

void DeleteCommand::redo() {
    if (octreeEditor->source()->deleteNode(nodes)) {
        octreeEditor->confirmUpdate();
    } else {
        qDebug() << "Failure delete node";
    }
}

AddCommand::AddCommand(OctreeEditor* octreeEditor, bool back) : octreeEditor(octreeEditor), back(back) {
    nodes = octreeEditor->selection();
}

void AddCommand::undo() {
    if (octreeEditor->source()->deleteNode(node)) {
        octreeEditor->confirmUpdate();
    } else {
        qDebug() << "Failure delete node";
    }
}

void AddCommand::redo() {
    if (octreeEditor->source()->addNode(nodes, back, node)) {
        octreeEditor->confirmUpdate();
    } else {
        qDebug() << "Failure add node";
    }
}

SplitCommand::SplitCommand(OctreeEditor* octreeEditor) : octreeEditor(octreeEditor) {
    nodes = octreeEditor->selection();
}

void SplitCommand::undo() {
    bool result = false;
    for (auto node: nodes) {
        result = octreeEditor->source()->mergeNode(*node.data());
    }
    if (result) {
        octreeEditor->confirmUpdate();
    } else {
        qDebug() << "Failure merge node";
    }
}

void SplitCommand::redo() {
    octreeEditor->split();
    octreeEditor->confirmUpdate();
}

MergeCommand::MergeCommand(OctreeEditor* octreeEditor) : octreeEditor(octreeEditor) {
    nodes = octreeEditor->selection();
}

void MergeCommand::undo() {
    octreeEditor->source()->createChildren(newNode);
    bool result = false;
    for (auto node: mergedNodes) {
        result = octreeEditor->source()->addNode(node);
    }
    if (result) {
        octreeEditor->confirmUpdate();
    } else {
        qDebug() << "Failure merge node";
    }
}

void MergeCommand::redo() {
    if (octreeEditor->source()->mergeNode(nodes, newNode, mergedNodes)) {
        octreeEditor->confirmUpdate();
    } else {
        qDebug() << "Failure merge node";
    }
}

ChangeColorCommand::ChangeColorCommand(OctreeEditor* octreeEditor, QColor color) : octreeEditor(octreeEditor), color(color) {
    nodes = octreeEditor->selection();
}

void ChangeColorCommand::undo() {
    bool result = false;
    for (auto node: nodes) {
        result = octreeEditor->source()->changeNodeColor(*node.data());
    }
    if (result) {
        octreeEditor->confirmUpdate();
    } else {
        qDebug() << "Failure change node color";
    }
}

void ChangeColorCommand::redo() {
    if (octreeEditor->source()->changeNodeColor(nodes, color)) {
        octreeEditor->confirmUpdate();
    } else {
        qDebug() << "Failure change node color";
    }
}

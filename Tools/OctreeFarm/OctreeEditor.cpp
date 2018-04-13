#include "OctreeEditor.h"
#include "Source.h"
#include "Octree/Octree.h"
#include <QtCore>
#include <QtGui>
#include <bitset>

namespace OctreeFarm {

OctreeEditor::OctreeEditor(QObject* parent) : QObject(parent) {
    createNew();
}

OctreeEditor::~OctreeEditor() {

}

void OctreeEditor::createNew() {
    octree.reset(new Origin::Octree);
    dataChanged();
}

void OctreeEditor::split(const Origin::Octree::Path& path) {
    octree->split(path);
    dataChanged();
}

bool OctreeEditor::save(const QString& fileName) {
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly)) {
        qDebug() << "Could not open file for writing";
        return false;
    }

    QTextStream out(&file);
    out << source->serialize();
    file.close();

    return true;
}

bool OctreeEditor::load(const QString& fileName) {
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly)) {
        qDebug() << "Could not open file for reading";
        return false;
    }
    QTextStream in(&file);
    QString data = in.readAll();
    source->create(data);

    file.close();

    storage = source->binary();
    dataChanged();

    return true;
}

void OctreeEditor::setIsModified(bool isModified) {
    if (this->isModified == isModified) return;
    this->isModified = isModified;
    emit isModifiedChanged(isModified);
}

int OctreeEditor::colorAttachOffset(int parent, int childIndex) {
//    int pageHeader = parent & -pageBytes;
//    int blockInfo = pageHeader + storage->at(pageHeader);
//    int attachData = blockInfo + blockInfoEnd;
//    int paletteNode = storage->at(attachData + parent - 1);
//    return attachData + (paletteNode >> 8) + std::bitset<8>(paletteNode & ((1 << childIndex) - 1)).count();
    return 0;
}

void OctreeEditor::confirmUpdate() {
    selection.clear();
    nodeDeselected();
    storage = source->binary();
    setIsModified(true);
    dataChanged();
}

void OctreeEditor::select(uint32_t parent, uint32_t scale, uint32_t childIndex, const glm::vec3& pos, bool append) {
    int offset = colorAttachOffset(parent, childIndex);

    QSharedPointer<Node> node(new Node);
    node->parent = parent;
    node->scale = scale;
    node->childIndex = childIndex;
    node->pos = pos;
    QColor color;

    int index = -1;
    for (int i = 0; i < selection.count(); i++) {
        if (selection.at(i)->parent == parent && selection.at(i)->childIndex == childIndex) {
            index = i;
            break;
        }
    }

    if (append) {
        if (index >= 0) { // Remove selection
            (*storage)[offset] = selection.at(index)->color;
            selection.remove(index);
            nodeDeselected();
        } else { // Append selection
            node->color = (*storage)[offset];
            (*storage)[offset] = selectionColor;
            selection.append(node);
            color.setRgba(node->color);
            nodeSelected(node->scale, childIndex, color);
        }
    } else if (index == -1 || selection.count() > 1) {
        deselect();
        node->color = (*storage)[offset];
        (*storage)[offset] = selectionColor;
        selection.append(node);
        color.setRgba(node->color);
        nodeSelected(node->scale, childIndex, color);
    }

    dataChanged();
}

void OctreeEditor::deselect() {
    if (selection.count()) {
        for (auto node: selection) {
            int address = colorAttachOffset(node->parent, node->childIndex);
            (*storage)[address] = node->color;
        }

        selection.clear();
        nodeDeselected();
        dataChanged();
    }
}

void OctreeEditor::copy() {
    if (selection.count()) {
        clipboard.color = selection.last().data()->color;
    }
}

void OctreeEditor::paste() {
    if (clipboard.color.isValid()) {
//        changeNodeColor(clipboard.color);
    }
}

} // OctreeFarm

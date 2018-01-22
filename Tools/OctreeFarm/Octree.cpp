#include "Octree.h"
#include <QtCore>
#include <QtGui>
#include "../../Source/Core/Utils.h"
#include <bitset>

namespace OctreeFarm {

Octree::Octree(QObject* parent) : QObject(parent) {
    worldToOctree = glm::inverse(octreeToWorld);
}

void Octree::createNew() {
    source.create();
    storage = source.binary();
}

bool Octree::save(const QString& fileName) {
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly)) {
        qDebug() << "Could not open file for writing";
        return false;
    }

    QTextStream out(&file);
    out << source.serialize();
    file.close();

    return true;
}

bool Octree::load(const QString& fileName) {
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly)) {
        qDebug() << "Could not open file for reading";
        return false;
    }
    QTextStream in(&file);
    QString data = in.readAll();
    source.create(data);

    file.close();

    storage = source.binary();
    dataChanged();

    return true;
}

void Octree::setIsModified(bool isModified) {
    if (isModified == isModified) return;
    isModified = isModified;
    emit isModifiedChanged(isModified);
}

int Octree::colorAttachOffset(int parent, int childIndex) {
//    int pageHeader = parent & -pageBytes;
//    int blockInfo = pageHeader + storage->at(pageHeader);
//    int attachData = blockInfo + blockInfoEnd;
//    int paletteNode = storage->at(attachData + parent - 1);
//    return attachData + (paletteNode >> 8) + std::bitset<8>(paletteNode & ((1 << childIndex) - 1)).count();
    return 0;
}

void Octree::confirmUpdate() {
    selection.clear();
    nodeDeselected();
    storage = source.binary();
    setIsModified(true);
    dataChanged();
}

void Octree::select(uint32_t parent, uint32_t scale, uint32_t childIndex, const glm::vec3& pos, bool append) {
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

void Octree::deselect() {
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

void Octree::copy() {
    if (selection.count()) {
        clipboard.color = selection.last().data()->color;
    }
}

void Octree::paste() {
    if (clipboard.color.isValid()) {
//        changeNodeColor(clipboard.color);
    }
}

} // OctreeFarm

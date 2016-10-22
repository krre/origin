#include "Octree.h"
#include <QtCore>
#include <QtGui>
#include "../../Source/Core/Utils.h"

Octree::Octree(QObject* parent) : QObject(parent) {
    m_worldToOctree = glm::inverse(m_octreeToWorld);
}

void Octree::createNew() {
    source.create();
    storage = source.binary();
    clipboard.fill = false;
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
    clipboard.fill = false;
    dataChanged();

    return true;
}

void Octree::setIsModified(bool isModified) {
    if (this->isModified == isModified) return;
    this->isModified = isModified;
    emit isModifiedChanged(isModified);
}

int Octree::colorAttachAddress(int parent, int childIndex) {
    int pageHeader = parent & -pageBytes;
    int blockInfo = pageHeader + storage->at(pageHeader);
    int attachData = blockInfo + blockInfoEnd;
    int paletteNode = storage->at(attachData + parent - 1);
    return attachData + (paletteNode >> 8) + Utils::bitCount8(paletteNode & ((1 << childIndex) - 1));
}

void Octree::confirmUpdate() {
    selection.clear();
    nodeDeselected();
    storage = source.binary();
    setIsModified(true);
    dataChanged();
}

void Octree::select(uint32_t parent, uint32_t scale, uint32_t childIndex, const glm::vec3& pos, bool append) {
    int address = colorAttachAddress(parent, childIndex);

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
            (*storage)[address] = selection.at(index)->color;
            selection.remove(index);
            nodeDeselected();
        } else { // Append selection
            node->color = (*storage)[address];
            (*storage)[address] = selectionColor;
            selection.append(node);
            color.setRgba(node->color);
            nodeSelected(childIndex, color);
        }
    } else if (index == -1 || selection.count() > 1) {
        deselect();
        node->color = (*storage)[address];
        (*storage)[address] = selectionColor;
        selection.append(node);
        color.setRgba(node->color);
        nodeSelected(childIndex, color);
    }

    dataChanged();
}

void Octree::changeNodeColor(const QColor& color) {
    if (source.changeNodeColor(selection, color)) {
        confirmUpdate();
    } else {
        qDebug() << "Failure change node color";
    }
}

void Octree::deselect() {
    if (selection.count()) {
        for (auto node: selection) {
            int address = colorAttachAddress(node->parent, node->childIndex);
            (*storage)[address] = node->color;
        }

        selection.clear();
        nodeDeselected();
        dataChanged();
    }
}

void Octree::splitNode() {
    if (source.splitNode(selection)) {
        confirmUpdate();
    } else {
        qDebug() << "Failure split node";
    }
}

void Octree::mergeNode() {
    if (source.mergeNode(selection)) {
        confirmUpdate();
    } else {
        qDebug() << "Failure merge node";
    }
}

void Octree::addNode() {
    if (source.addNode(selection, QGuiApplication::keyboardModifiers() == Qt::ShiftModifier)) {
        confirmUpdate();
    } else {
        qDebug() << "Failure add node";
    }
}

void Octree::deleteNode() {
    if (source.deleteNode(selection)) {
        confirmUpdate();
    } else {
        qDebug() << "Failure delete node";
    }
}

void Octree::copy() {
    qDebug() << "copy";
}

void Octree::paste() {
    qDebug() << "paste";
}

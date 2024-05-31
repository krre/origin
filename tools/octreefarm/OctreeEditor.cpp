#include "OctreeEditor.h"
#include "Source.h"
#include "octree/Octree.h"
#include <QtCore>
#include <QtGui>
#include <bitset>

OctreeEditor::OctreeEditor(QObject* parent) : QObject(parent) {
    createNew();
}

OctreeEditor::~OctreeEditor() {

}

void OctreeEditor::createNew() {
    m_octree.reset(new Octree::Octree);
    dataChanged();
}

void OctreeEditor::split(const Octree::Octree::Path& path) {
    m_octree->split(path);
    dataChanged();
}

bool OctreeEditor::save(const QString& fileName) {
    m_octree->save(fileName.toStdString());
    return true;
}

bool OctreeEditor::load(const QString& fileName) {
    m_octree->load(fileName.toStdString());
    dataChanged();

    return true;
}

void OctreeEditor::setModified(bool modified) {
    if (m_modified == modified) return;
    m_modified = modified;
    emit isModifiedChanged(modified);
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
    m_selection.clear();
    nodeDeselected();
    storage = m_source->binary();
    setModified(true);
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
    for (int i = 0; i < m_selection.count(); i++) {
        if (m_selection.at(i)->parent == parent && m_selection.at(i)->childIndex == childIndex) {
            index = i;
            break;
        }
    }

    if (append) {
        if (index >= 0) { // Remove selection
            (*storage)[offset] = m_selection.at(index)->color;
            m_selection.remove(index);
            nodeDeselected();
        } else { // Append selection
            node->color = (*storage)[offset];
            (*storage)[offset] = selectionColor;
            m_selection.append(node);
            color.setRgba(node->color);
            nodeSelected(node->scale, childIndex, color);
        }
    } else if (index == -1 || m_selection.count() > 1) {
        deselect();
        node->color = (*storage)[offset];
        (*storage)[offset] = selectionColor;
        m_selection.append(node);
        color.setRgba(node->color);
        nodeSelected(node->scale, childIndex, color);
    }

    dataChanged();
}

void OctreeEditor::deselect() {
    if (m_selection.count()) {
        for (auto node: m_selection) {
            int address = colorAttachOffset(node->parent, node->childIndex);
            (*storage)[address] = node->color;
        }

        m_selection.clear();
        nodeDeselected();
        dataChanged();
    }
}

void OctreeEditor::copy() {
    if (m_selection.count()) {
        clipboard.color = m_selection.last().data()->color;
    }
}

void OctreeEditor::paste() {
    if (clipboard.color.isValid()) {
//        changeNodeColor(clipboard.color);
    }
}

#include "Octree.h"
#include <QtCore>
#include <QtGui>
#include "Utils.h"

Octree::Octree(QObject* parent) : QObject(parent) {
    m_worldToOctree = glm::inverse(m_octreeToWorld);
}

void Octree::createNew() {
    source.create();
    storage = source.binary();

    /* Example
     *
    // Header
    storage.append(0x00000002); // => Block info
    // Nodes
    storage.append(0x0000FF00); // 0000 0000 0000 0000 | 1111 1111 | 0000 0000
    // Block info
    storage.append(0x00000000);
    // Attach data
    storage.append(0x000001FF); // 0000 0000 0000 0000 0000 0001 | 1111 1111
    // Colors
    storage.append(defaultColor);
    storage.append(defaultColor);
    storage.append(defaultColor);
    storage.append(defaultColor);
    storage.append(defaultColor);
    storage.append(defaultColor);
    storage.append(defaultColor);
    storage.append(defaultColor);
    */
}

void Octree::createTest() {
    /*
    storage.clear();
    // Test data
    // Header
    data->push_back(0x00000004); // => Block info
    // Nodes
    data->push_back(0x00027F08); // 0000 0000 0000 0010 | 0111 1111 | 0000 1000
    data->push_back(0x0002BF80); // 0000 0000 0000 0010 | 1011 1111 | 1000 0000
    data->push_back(0x00008F00); // 0000 0000 0000 0000 | 1000 1111 | 0000 0000
    // Block info
    data->push_back(0x00000000);
    // Attach data
    data->push_back(0x0000037F); // 0000 0000 0000 0000 0000 0003 | 0111 1111
    data->push_back(0x00000A99); // 0000 0000 0000 0000 0000 1010 | 1001 1001
    data->push_back(0x00000000); // 0000 0000 0000 0000 0000 0000 | 0000 0000
    // Colors
    data->push_back(0x044A00FF);
    data->push_back(0xA30000FF);
    data->push_back(0x13DAFFFF);
    data->push_back(0x7E4681FF);
    data->push_back(0xFF0011FF);
    data->push_back(0x903472FF);
    data->push_back(0xAD7D4DFF);

    data->push_back(0x5A1681FF);
    data->push_back(0x6B38ACFF);
    data->push_back(0x5DD772FF);
    data->push_back(0xC5651FFF);
    return data;
    */
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
    if (isModified == m_isModified) return;
    m_isModified = isModified;
    emit isModifiedChanged(isModified);
}

int Octree::colorAttachAddress(int parent, int childIndex) {
    int pageHeader = parent & -pageBytes;
    int blockInfo = pageHeader + storage->at(pageHeader);
    int attachData = blockInfo + blockInfoEnd;
    int paletteNode = storage->at(attachData + parent - 1);
    return attachData + (paletteNode >> 8) + Utils::bitCount8(paletteNode & ((1 << childIndex) - 1));
}

void Octree::select(uint32_t parent, uint32_t childIndex, bool append) {
    int address = colorAttachAddress(parent, childIndex);

    QSharedPointer<Node> node;
    node.reset(new Node);
    node->parent = parent;
    node->childIndex = childIndex;
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
            (*storage)[address] = m_selection.at(index)->color;
            m_selection.remove(index);
            nodeDeselected();
        } else { // Append selection
            node->color = (*storage)[address];
            (*storage)[address] = selectionColor;
            m_selection.append(node);
            color.setRgba(node->color);
            nodeSelected(childIndex, color);
        }
    } else if (index == -1 || m_selection.count() > 1) {
        deselect();
        node->color = (*storage)[address];
        (*storage)[address] = selectionColor;
        m_selection.append(node);
        color.setRgba(node->color);
        nodeSelected(childIndex, color);
    }

    dataChanged();
}

void Octree::changeNodeColor(const QColor& color) {
    if (source.changeNodeColor(m_selection, color)) {
        m_selection.clear();
        nodeDeselected();
        storage = source.binary();
        setIsModified(true);
        dataChanged();
    } else {
        qDebug() << "Failure change node color";
    }
}

void Octree::deselect() {
    if (m_selection.count()) {
        for (auto node: m_selection) {
            int address = colorAttachAddress(node->parent, node->childIndex);
            (*storage)[address] = node->color;
        }

        m_selection.clear();
        nodeDeselected();
        dataChanged();
    }
}

void Octree::splitNode() {
    if (source.splitNode(m_selection)) {
        m_selection.clear();
        nodeDeselected();
        storage = source.binary();
        setIsModified(true);
        dataChanged();
    } else {
        qDebug() << "Failure split node";
    }
}

void Octree::mergeNode() {
    if (source.mergeNode(m_selection)) {
        m_selection.clear();
        nodeDeselected();
        storage = source.binary();
        setIsModified(true);
        dataChanged();
    } else {
        qDebug() << "Failure merge node";
    }
}

void Octree::addNode() {
    qDebug() << "add";
}

void Octree::deleteNode() {
    if (source.deleteNode(m_selection)) {
        m_selection.clear();
        nodeDeselected();
        storage = source.binary();
        setIsModified(true);
        dataChanged();
    } else {
        qDebug() << "Failure delete node";
    }
}

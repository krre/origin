#include "Octree.h"
#include <QtCore>

Octree::Octree(QObject* parent) : QObject(parent) {
    m_worldToOctree = glm::inverse(m_octreeToWorld);
}

void Octree::createNew() {
    storage.clear();

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
}

void Octree::createTest() {
    storage.clear();
    // Test data
    // Header
    storage.append(0x00000003); // => Block info
    // Nodes
    storage.append(0x00027F08); // 0000 0000 0000 0010 | 0111 1111 | 0000 1000
    storage.append(0x0000BF00); // 0000 0000 0000 0000 | 1101 1111 | 0000 0000
    // Block info
    storage.append(0x00000000);
    // Attach data
    storage.append(0x0000027F); // 0000 0000 0000 0000 0000 0002 | 0111 1111
    storage.append(0x00000999); // 0000 0000 0000 0000 0000 1001 | 1001 1001
    // Colors
    storage.append(0x044A00FF);
    storage.append(0xA30000FF);
    storage.append(0x13DAFFFF);
    storage.append(0x7E4681FF);
    storage.append(0xFF0011FF);
    storage.append(0x903472FF);
    storage.append(0xAD7D4DFF);

    storage.append(0x5A1681FF);
    storage.append(0x6B38ACFF);
    storage.append(0x5DD772FF);
    storage.append(0xC5651FFF);
}

bool Octree::save(const QString& fileName) {
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly)) {
        qDebug() << "Could not open file for writing";
        return false;
    }
    QDataStream out(&file);
    for (auto it: storage) {
        out << it;
    }
    file.close();

    return true;
}

bool Octree::load(const QString& fileName) {
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly)) {
        qDebug() << "Could not open file for reading";
        return false;
    }
    QDataStream in(&file);
    uint32_t word;
    storage.clear();
    while (!in.atEnd()) {
        in >> word;
        storage.append(word);
    }
    file.close();

    return true;
}

void Octree::setIsModified(bool isModified) {
    if (isModified == m_isModified) return;
    m_isModified = isModified;
    emit isModifiedChanged(isModified);
}

int Octree::bitCount8(int value) {
    int count = 0;
    for (int i = 0; i < 8; i++) {
        if ((value & 1) == 1) {
            count++;
        }
        value >>= 1;
    }

    return count;
}

int Octree::colorAttachAddress(int parent, int childIndex) {
    int pageHeader = parent & -pageBytes;
    int blockInfo = pageHeader + storage.at(pageHeader);
    int attachData = blockInfo + blockInfoEnd;
    int paletteNode = storage.at(attachData + parent - 1);
    return attachData + (paletteNode >> 8) + bitCount8(paletteNode & 0xFF & ((1 << childIndex) - 1));
}

void Octree::select(Node node, bool append) {
    if (!append) {
        deselect();
    }
    int address = colorAttachAddress(node.parent, node.childIndex);
    node.color = storage[address];
    storage[address] = 0xFFFFFF00;

    m_selection.append(node);

    dataChanged();
}

void Octree::deselect() {
    if (m_selection.count()) {
        for (auto node: m_selection) {
            int address = colorAttachAddress(node.parent, node.childIndex);
            storage[address] = node.color;
        }

        m_selection.clear();
        dataChanged();
    }
}

#include "Octree.h"

Octree::Octree(QObject* parent) : QObject(parent) {
    m_worldToOctree = glm::inverse(m_octreeToWorld);

    // Test data
    // Header
    storage.push_back(0x00000003); // => Block info
    // Nodes
    storage.push_back(0x00027F08); // 0000 0000 0000 0010 | 0111 1111 | 0000 1000
    storage.push_back(0x0000BF00); // 0000 0000 0000 0000 | 1101 1111 | 0000 0000
    // Block info
    storage.push_back(0x00000000);
    // Attach data
    storage.push_back(0x0000027F); // 0000 0000 0000 0000 0000 0002 | 0111 1111
    storage.push_back(0x00000999); // 0000 0000 0000 0000 0000 1001 | 1001 1001
    // Colors
    storage.push_back(0x044A00FF);
    storage.push_back(0xA30000FF);
    storage.push_back(0x13DAFFFF);
    storage.push_back(0x7E4681FF);
    storage.push_back(0xFF0011FF);
    storage.push_back(0x903472FF);
    storage.push_back(0xAD7D4DFF);

    storage.push_back(0x5A1681FF);
    storage.push_back(0x6B38ACFF);
    storage.push_back(0x5DD772FF);
    storage.push_back(0xC5651FFF);
}

void Octree::createNew() {
    qDebug() << "New octree";
}

void Octree::save(const QString& filePath) {
    qDebug() << "Save with path" << filePath;
}

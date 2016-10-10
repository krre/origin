#include "Source.h"
#include "Octree.h"
#include "Utils.h"
#include <QtCore>
#include <bitset>

Source::Source(QObject* parent) : QObject(parent) {

}

void Source::create(const QString& string) {
    if (string.isEmpty()) {
        for (int i = 0; i < 8; i++) {
            json node;
            node["color"] = QColor(defaultColor).name(QColor::HexArgb).toStdString();
            root[QString::number(i).toStdString()] = node;
        }
    } else {
        root = json::parse(string.toStdString());
    }
}

QString Source::serialize() {
    std::string dump = root.dump(4);
    return QString::fromStdString(dump);
}

QSharedPointer<QVector<uint32_t>> Source::binary() {
    QSharedPointer<QVector<uint32_t>> data;
    data.reset(new QVector<uint32_t>());

    // Append header
    data->append(0);

    QVector<json::object_t*> octreesFirst;
    QVector<json::object_t*> octreesSecond;

    json::object_t* parent = root.get_ptr<json::object_t*>();
    octreesFirst.append(parent);

    QVector<uint32_t> colorDescriptors;
    QVector<uint32_t> colors;
    uint32_t offset = 0;

    std::cout << root.dump(4) << std::endl;

    // Append node descriptors
    while (true) {

        uint32_t nodeDescriptor = 0;
        uint32_t colorDescriptor = 0;
        octreesSecond.clear();
        json::object_t* octree = octreesFirst.takeFirst();

        for (auto& node: (*octree)) {
            nodeDescriptor |= (1 << (8 + std::stoi(node.first))); // Valid nodes

            json::iterator iter = node.second.find("children");
            if (iter != node.second.end()) {
                nodeDescriptor |= (1 << std::stoi(node.first)); // Non-leaf nodes
                octreesSecond.append(iter.value().get_ptr<json::object_t*>());
            }

            iter = node.second.find("color");
            if (iter != node.second.end()) {
                colorDescriptor |= (1 << std::stoi(node.first)); // Valid colors
                std::string nameColor = (*octree)[node.first]["color"];
                QColor color(nameColor.c_str());
                colors.append(color.rgba());
            }
        }


        int childNum = Utils::bitCount8(nodeDescriptor);
        if (childNum) {
            if (data->count() == 1) { // First descriptor in vector
                nodeDescriptor |= (1 << 17); // Set offset to 1
            } else {
                uint32_t lastDescriptor = data->at(offset);
                nodeDescriptor |= ((lastDescriptor >> 17) + Utils::bitCount8(lastDescriptor) - 1);
            }
        }

        data->append(nodeDescriptor);

        colorDescriptors.append(colorDescriptor);
        offset++;
        parents[offset] = octree;

        if (octreesFirst.isEmpty()) {
            if (octreesSecond.isEmpty()) {
                break;
            } else {
                octreesFirst = octreesSecond;
            }
        }
    }

    (*data)[0] = offset + 1; // Address to block info

    // Append block info
    data->append(0);

    // Append attach descriptors
    offset = colorDescriptors.count();
    for (int i = 0 ; i < colorDescriptors.count(); i++) {
        uint32_t colorDescriptor = colorDescriptors[i];
        int numColors = Utils::bitCount8(colorDescriptor);
        if (numColors) {
            colorDescriptor |= (offset << 8);
            offset += numColors;
        }
        data->append(colorDescriptor);
    }

    // Append colors
    for (int i = 0; i < colors.count(); i++) {
        data->append(colors[i]);
    }

    qDebug() << *data;

    return data;
}

bool Source::changeNodeColor(const QVector<QSharedPointer<Node>>& selection, const QColor& color) {
    if (!selection.count()) return false;

    for (int i = 0; i < selection.count(); i++) {
        Node* node = selection.at(i).data();
        json::object_t* parent = parents[node->parent];
        (*parent)[std::to_string(node->childIndex)]["color"] = color.name(QColor::HexArgb).toStdString();
    }

    return true;
}

bool Source::deleteNode(const QVector<QSharedPointer<Node>>& selection) {
    if (!selection.count()) return false;

    for (int i = 0; i < selection.count(); i++) {
        Node* node = selection.at(i).data();
        QVector<int> path = posToPath(node->pos, node->scale);
        json::object_t* parentNode = findNode(path, path.count() - 2);
        (*parentNode).erase(std::to_string(path.last()));
    }

    return true;
}

bool Source::splitNode(const QVector<QSharedPointer<Node>>& selection) {
    if (!selection.count()) return false;

    for (int i = 0; i < selection.count(); i++) {
        Node* node = selection.at(i).data();
        json::object_t* parent = parents[node->parent];
        json children;
        for (int i = 0; i < 8; i++) {
            json obj;
            obj["color"] = QColor(defaultColor).name(QColor::HexArgb).toStdString();
            children[std::to_string(i)] = obj;
        }

        (*parent)[std::to_string(node->childIndex)]["children"] = children;
    }

    return true;
}

bool Source::mergeNode(const QVector<QSharedPointer<Node>>& selection) {
    if (!selection.count()) return false;

    Node* node = selection.at(0).data();
    QVector<int> path = posToPath(node->pos, node->scale);
    if (path.count() > 1) {
        int parentIndex = path.count() - 2;
        json::object_t* parentNode = findNode(path, parentIndex);
        (*parentNode).erase("children");
        return true;
    } else {
        return false;
    }
}

bool Source::addNode(const QVector<QSharedPointer<Node>>& selection) {
    if (!selection.count()) return false;

    return false;
}

json::object_t* Source::findNode(const QVector<int>& path, int index) {
    json::object_t* node = root.get_ptr<json::object_t*>();
    for (int i = 0; i <= index; i++) {
        node = (*node)[std::to_string(path.at(i))].get_ptr<json::object_t*>();
        if (i != index) {
            node = (*node)["children"].get_ptr<json::object_t*>();
        }
    }
    return node;
}

QVector<int> Source::posToPath(const glm::uvec3& pos, int scale) {
    QVector<int> path;
    int s_max = 23; // from Voxel.frag
    std::bitset<32> bitsX(pos.x);
    std::bitset<32> bitsY(pos.y);
    std::bitset<32> bitsZ(pos.z);

    for (int i = s_max - 1; i >= scale; i--) {
        int index = 0;
        index |= bitsX[i];
        index |= bitsY[i] << 1;
        index |= bitsZ[i] << 2;
        path.append(index);
    }

    return path;
}

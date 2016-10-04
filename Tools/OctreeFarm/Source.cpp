#include "Source.h"
#include "Octree.h"
#include "Utils.h"
#include <QtCore>

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
    data->append(0); // Header

    json::object_t* parent = root.get_ptr<json::object_t*>();
    uint32_t offset = 0;
    QVector<uint32_t> colorDescriptors;
    QVector<uint32_t> colors;

    // Append node descriptors
    while (true) {

        uint32_t nodeDescriptor = 0;
        uint32_t colorDescriptor = 0;

        for (auto& node: (*parent)) {
            nodeDescriptor |= (1 << (8 + std::stoi(node.first)));

            json::iterator iter = node.second.find("children");
            if (iter != node.second.end()) {
                nodeDescriptor |= (1 << std::stoi(node.first));
            }

            iter = node.second.find("color");
            if (iter != node.second.end()) {
                colorDescriptor |= (1 << std::stoi(node.first));
                std::string nameColor = (*parent)[node.first]["color"];
                QColor color(nameColor.c_str());
                colors.append(color.rgba());
            }
        }

        data->append(nodeDescriptor);
        colorDescriptors.append(colorDescriptor);
        offset++;
        parents[offset] = parent;

        break;
    }

    (*data)[0] = offset + 1; // Address to block info

    // Append block info
    data->append(0);

    // Append attach descriptors
    offset = colorDescriptors.count();
    for (int i = 0 ; i < colorDescriptors.count(); i++) {
        uint32_t colorDescriptor = colorDescriptors[i];
        colorDescriptor |= (offset << 8);
        data->append(colorDescriptor);
        offset += Utils::bitCount8(colorDescriptor);
    }

    // Append colors
    for (int i = 0; i < colors.count(); i++) {
        data->append(colors[i]);
    }

    return data;
}

bool Source::deleteNode(const QVector<QSharedPointer<Node>>& selection) {
    if (!selection.count()) return false;

    for (int i = 0; i < selection.count(); i++) {
        Node* node = selection.at(i).data();
        json::object_t* parent = parents[node->parent];
        parent->erase(std::to_string(node->childIndex));
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
            children[std::to_string(i)] = json::object();
        }

        (*parent)[std::to_string(node->childIndex)]["children"] = children;
    }

    return true;
}

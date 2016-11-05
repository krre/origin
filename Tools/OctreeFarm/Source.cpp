#include "Source.h"
#include "Octree.h"
#include "Defines.h"
#include "../../Source/Core/Utils.h"
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
    std::shared_ptr<std::vector<uint32_t>> dataStd = Utils::jsonToBinary(root);
    QVector<uint32_t>* data = new QVector<uint32_t>(QVector<uint32_t>::fromStdVector(*dataStd));

#if BINARY_PRINT == 1
    for (auto value: *data) {
        qDebug() << QString::fromStdString(Utils::uintToBinaryString(value)) << value;
    }
#endif

    return QSharedPointer<QVector<uint32_t>>(data);
}

bool Source::changeNodeColor(const QVector<QSharedPointer<Node>>& selection, const QColor& color) {
    if (!selection.count()) return false;

    for (int i = 0; i < selection.count(); i++) {
        Node* node = selection.at(i).data();
        QVector<int> path = posToPath(node->pos, node->scale);
        json::object_t* currentNode = findNode(path, path.count() - 1);
        (*currentNode)["color"] = color.name(QColor::HexArgb).toStdString();
    }

    return true;
}

bool Source::changeNodeColor(const Node& node) {
    QVector<int> path = posToPath(node.pos, node.scale);
    json::object_t* currentNode = findNode(path, path.count() - 1);
    (*currentNode)["color"] = QColor(node.color).name(QColor::HexArgb).toStdString();

    return true;
}

bool Source::deleteNode(const QVector<QSharedPointer<Node>>& selection) {
    if (!selection.count()) return false;

    for (int i = 0; i < selection.count(); i++) {
        Node* node = selection.at(i).data();
        QVector<int> path = posToPath(node->pos, node->scale);
        json::object_t* parentNode;
        if (path.count() == 1) {
            parentNode = root.get_ptr<json::object_t*>();
        } else {
            parentNode = findNode(path, path.count() - 2);
            parentNode = (*parentNode)["children"].get_ptr<json::object_t*>();
        }
        (*parentNode).erase(std::to_string(path.last()));
    }

    return true;
}

bool Source::deleteNode(const Node& node) {
    QVector<int> path = posToPath(node.pos, node.scale);
    json::object_t* parentNode;
    if (path.count() == 1) {
        parentNode = root.get_ptr<json::object_t*>();
    } else {
        parentNode = findNode(path, path.count() - 2);
        parentNode = (*parentNode)["children"].get_ptr<json::object_t*>();
    }
    (*parentNode).erase(std::to_string(path.last()));

    return true;
}

bool Source::splitNode(const QVector<QSharedPointer<Node>>& selection) {
    if (!selection.count()) return false;

    for (int i = 0; i < selection.count(); i++) {
        Node* node = selection.at(i).data();
        QVector<int> path = posToPath(node->pos, node->scale);
        json::object_t* parentNode;
        if (path.count() == 1) {
            parentNode = root.get_ptr<json::object_t*>();
        } else {
            parentNode = findNode(path, path.count() - 2);
            parentNode = (*parentNode)["children"].get_ptr<json::object_t*>();
        }
        json children;
        for (int i = 0; i < 8; i++) {
            children[std::to_string(i)]["color"] = (*parentNode)[std::to_string(path.last())]["color"];
        }

        (*parentNode)[std::to_string(path.last())]["children"] = children;
    }

    return true;
}

bool Source::mergeNode(const QVector<QSharedPointer<Node>>& selection, Node& newNode, QVector<Node>& mergedNodes) {
    if (!selection.count()) return false;

    Node* node = selection.at(0).data();
    QVector<int> path = posToPath(node->pos, node->scale);
    if (path.count() > 1) {
        int parentIndex = path.count() - 2;
        json::object_t* parentNode = findNode(path, parentIndex);
        json::object_t* children = (*parentNode)["children"].get_ptr<json::object_t*>();
        for (int i = 0; i < 8; i++) {
            auto iter = (*children).find(std::to_string(i));
            if (iter != (*children).end()) {
                Node childNode;
                childNode.scale = node->scale;
                QColor color(QString::fromStdString((*children)[std::to_string(i)]["color"]));
                childNode.color = color.rgba();
                path[path.count() - 1] = i;
                childNode.pos = pathToPos(path);
                mergedNodes.append(childNode);
            }
        }
        newNode.scale = node->scale + 1;
        path.removeLast();
        newNode.pos = pathToPos(path);
        (*parentNode).erase("children");
        return true;
    } else {
        return false;
    }
}

bool Source::mergeNode(const Node& node) {
    QVector<int> path = posToPath(node.pos, node.scale);
    if (path.count() > 0) {
        int currentIndex = path.count() - 1;
        json::object_t* currentNode = findNode(path, currentIndex);
        (*currentNode).erase("children");
        return true;
    } else {
        return false;
    }
}

bool Source::addNode(const QVector<QSharedPointer<Node>>& selection, bool back, Node& newNode) {
    if (!selection.count()) return false;

    Node* node = selection.at(0).data();
    QVector<int> path = posToPath(node->pos, node->scale);
    json::object_t* parentNode;
    if (path.count() == 1) {
        parentNode = root.get_ptr<json::object_t*>();
    } else {
        parentNode = findNode(path, path.count() - 2);
        parentNode = (*parentNode)["children"].get_ptr<json::object_t*>();
    }

    if ((*parentNode).size() == 8) {
        return false;
    }

    int i = path.last();

    // Find next or previous empty node
    while (true) {
        if (back) {
            i--;
            if (i < 0) {
                i = 7;
            }
        } else {
            i++;
            if (i > 7) {
                i = 0;
            }
        }

        auto iter = (*parentNode).find(std::to_string(i));
        if (iter == (*parentNode).end()) {
            (*parentNode)[std::to_string(i)]["color"] = QColor(defaultColor).name(QColor::HexArgb).toStdString();
            path[path.count() - 1] = i; // Write to path finded node index
            newNode.pos = pathToPos(path);
            newNode.scale = node->scale;
            break;
        }
    }

    return true;
}

bool Source::addNode(const Node& node) {
    QVector<int> path = posToPath(node.pos, node.scale);
    json::object_t* parentNode;
    if (path.count() == 1) {
        parentNode = root.get_ptr<json::object_t*>();
    } else {
        parentNode = findNode(path, path.count() - 2);
        parentNode = (*parentNode)["children"].get_ptr<json::object_t*>();
    }

    if ((*parentNode).size() == 8) {
        return false;
    }

    int i = path.last();
    (*parentNode)[std::to_string(i)]["color"] = QColor(node.color).name(QColor::HexArgb).toStdString();

    return true;
}

void Source::createChildren(const Node& node) {
    QVector<int> path = posToPath(node.pos, node.scale);
    json::object_t* jNode = findNode(path, path.count() - 1);
    (*jNode)["children"] = json::object();
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

QVector<int> Source::posToPath(const glm::vec3& pos, int scale) {
    QVector<int> path;
    int s_max = 23; // from Voxel.frag
    std::bitset<32> bitsX(Utils::floatToUint(pos.x));
    std::bitset<32> bitsY(Utils::floatToUint(pos.y));
    std::bitset<32> bitsZ(Utils::floatToUint(pos.z));

    for (int i = s_max - 1; i >= scale; i--) {
        int index = 0;
        index |= bitsX[i];
        index |= bitsY[i] << 1;
        index |= bitsZ[i] << 2;
        path.append(index);
    }

    return path;
}

glm::vec3 Source::pathToPos(const QVector<int> path) {
    glm::vec3 pos = glm::vec3(1.0);
    int s_max = 23; // from Voxel.frag
    int i = s_max - 1;
    std::bitset<32> bitsX(Utils::floatToUint(pos.x));
    std::bitset<32> bitsY(Utils::floatToUint(pos.y));
    std::bitset<32> bitsZ(Utils::floatToUint(pos.z));

    for (auto index: path) {
        bitsX[i] = index & 1;
        bitsY[i] = (index >> 1) & 1;
        bitsZ[i] = (index >> 2) & 1;
        i--;
    }

    pos.x = Utils::uintToFloat(bitsX.to_ullong());
    pos.y = Utils::uintToFloat(bitsY.to_ullong());
    pos.z = Utils::uintToFloat(bitsZ.to_ullong());

    return pos;
}

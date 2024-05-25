#include "Source.h"
#include "OctreeEditor.h"
#include "Defines.h"
#include <QtCore>
#include <bitset>

namespace OctreeFarm {

const uint32_t DEFAULT_COLOR = 0xFF4681FF;

Source::Source(QObject* parent) : QObject(parent) {

}

void Source::create(const QString& string) {
    if (string.isEmpty()) {
        for (int i = 0; i < 8; i++) {
            root[QString::number(i)] = { { "color",  QColor(DEFAULT_COLOR).name(QColor::HexArgb) } };
        }
    } else {
        root = QJsonDocument::fromVariant(QVariant(string)).object();
    }
}

QString Source::serialize() {
    QJsonDocument doc(root);
    return QString(doc.toJson());
}

QSharedPointer<QVector<uint32_t>> Source::binary() {
//    std::shared_ptr<std::vector<uint32_t>> dataStd = Origin::Utils::jsonToBinary(root);
//    QVector<uint32_t>* data = new QVector<uint32_t>(QVector<uint32_t>::fromStdVector(*dataStd));

#if BINARY_PRINT == 1
    for (auto value: *data) {
        qDebug() << QString::fromStdString(Utils::uintToBinaryString(value)) << value;
    }
#endif

//    return QSharedPointer<QVector<uint32_t>>(data);
    return QSharedPointer<QVector<uint32_t>>();
}

bool Source::changeNodeColor(const QVector<QSharedPointer<Node>>& selection, const QColor& color) {
    if (!selection.count()) return false;

    for (int i = 0; i < selection.count(); i++) {
        Node* node = selection.at(i).data();
        QVector<int> path = posToPath(node->pos, node->scale);
        QJsonObject currentNode = findNode(path, path.count() - 1);
        currentNode["color"] = color.name(QColor::HexArgb);
    }

    return true;
}

bool Source::changeNodeColor(const Node& node) {
    QVector<int> path = posToPath(node.pos, node.scale);
    QJsonObject currentNode = findNode(path, path.count() - 1);
    currentNode["color"] = QColor(node.color).name(QColor::HexArgb);

    return true;
}

bool Source::deleteNode(const QVector<QSharedPointer<Node>>& selection) {
    if (!selection.count()) return false;

    for (int i = 0; i < selection.count(); i++) {
        Node* node = selection.at(i).data();
        QVector<int> path = posToPath(node->pos, node->scale);
        QJsonObject parentNode;
        if (path.count() == 1) {
            parentNode = root;
        } else {
            parentNode = findNode(path, path.count() - 2);
            parentNode = parentNode["children"].toObject();
        }
        parentNode.remove(QString::number(path.last()));
    }

    return true;
}

bool Source::deleteNode(const Node& node) {
    QVector<int> path = posToPath(node.pos, node.scale);
    QJsonObject parentNode;
    if (path.count() == 1) {
        parentNode = root;
    } else {
        parentNode = findNode(path, path.count() - 2);
        parentNode = parentNode["children"].toObject();
    }
    parentNode.remove(QString::number(path.last()));

    return true;
}

bool Source::splitNode(const QVector<QSharedPointer<Node>>& selection) {
    if (!selection.count()) return false;

    for (int i = 0; i < selection.count(); i++) {
        Node* node = selection.at(i).data();
        QVector<int> path = posToPath(node->pos, node->scale);
        QJsonObject parentNode;
        if (path.count() == 1) {
            parentNode = root;
        } else {
            parentNode = findNode(path, path.count() - 2);
            parentNode = parentNode["children"].toObject();
        }
        QJsonObject children;
        for (int i = 0; i < 8; i++) {
            children[QString::number(i)].toObject()["color"] = parentNode[QString::number(path.last())].toObject()["color"];
        }

        parentNode[QString::number(path.last())].toObject()["children"] = children;
    }

    return true;
}

bool Source::mergeNode(const QVector<QSharedPointer<Node>>& selection, Node& newNode, QVector<Node>& mergedNodes) {
    if (!selection.count()) return false;

    Node* node = selection.at(0).data();
    QVector<int> path = posToPath(node->pos, node->scale);
    if (path.count() > 1) {
        int parentIndex = path.count() - 2;
        QJsonObject parentNode = findNode(path, parentIndex);
        QJsonObject children = parentNode["children"].toObject();
        for (int i = 0; i < 8; i++) {
            auto iter = children.find(QString::number(i));
            if (iter != children.end()) {
                Node childNode;
                childNode.scale = node->scale;
                QColor color(children[QString::number(i)].toObject()["color"].toString());
                childNode.color = color.rgba();
                path[path.count() - 1] = i;
                childNode.pos = pathToPos(path);
                mergedNodes.append(childNode);
            }
        }
        newNode.scale = node->scale + 1;
        path.removeLast();
        newNode.pos = pathToPos(path);
        parentNode.remove("children");
        return true;
    } else {
        return false;
    }
}

bool Source::mergeNode(const Node& node) {
    QVector<int> path = posToPath(node.pos, node.scale);
    if (path.count() > 0) {
        int currentIndex = path.count() - 1;
        QJsonObject currentNode = findNode(path, currentIndex);
        currentNode.remove("children");
        return true;
    } else {
        return false;
    }
}

bool Source::addNode(const QVector<QSharedPointer<Node>>& selection, bool back, Node& newNode) {
    if (!selection.count()) return false;

    Node* node = selection.at(0).data();
    QVector<int> path = posToPath(node->pos, node->scale);
    QJsonObject parentNode;
    if (path.count() == 1) {
        parentNode = root;
    } else {
        parentNode = findNode(path, path.count() - 2);
        parentNode = parentNode["children"].toObject();
    }

    if (parentNode.size() == 8) {
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

        auto iter = parentNode.find(QString::number(i));
        if (iter == parentNode.end()) {
            parentNode[QString::number(i)].toObject()["color"] = QColor(DEFAULT_COLOR).name(QColor::HexArgb);
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
    QJsonObject parentNode;
    if (path.count() == 1) {
        parentNode = root;
    } else {
        parentNode = findNode(path, path.count() - 2);
        parentNode = parentNode["children"].toObject();
    }

    if (parentNode.size() == 8) {
        return false;
    }

    parentNode[QString::number(path.last())].toObject()["color"] = QColor(node.color).name(QColor::HexArgb);

    return true;
}

void Source::createChildren(const Node& node) {
    QVector<int> path = posToPath(node.pos, node.scale);
    QJsonObject jNode = findNode(path, path.count() - 1);
    jNode["children"] = QJsonObject();
}

QJsonObject Source::findNode(const QVector<int>& path, int index) {
    QJsonObject node = root;
    for (int i = 0; i <= index; i++) {
        node = node[QString::number(path.at(i))].toObject();
        if (i != index) {
            node = node["children"].toObject();
        }
    }
    return node;
}

QVector<int> Source::posToPath(const glm::vec3& pos, int scale) {
    QVector<int> path;
    int s_max = 23; // from Voxel.frag
//    std::bitset<32> bitsX(Origin::Utils::floatToUint(pos.x));
//    std::bitset<32> bitsY(Origin::Utils::floatToUint(pos.y));
//    std::bitset<32> bitsZ(Origin::Utils::floatToUint(pos.z));

//    for (int i = s_max - 1; i >= scale; i--) {
//        int index = 0;
//        index |= bitsX[i];
//        index |= bitsY[i] << 1;
//        index |= bitsZ[i] << 2;
//        path.append(index);
//    }

    return path;
}

glm::vec3 Source::pathToPos(const QVector<int> path) {
    glm::vec3 pos = glm::vec3(1.0);
    int s_max = 23; // from Voxel.frag
    int i = s_max - 1;
//    std::bitset<32> bitsX(Origin::Utils::floatToUint(pos.x));
//    std::bitset<32> bitsY(Origin::Utils::floatToUint(pos.y));
//    std::bitset<32> bitsZ(Origin::Utils::floatToUint(pos.z));

//    for (auto index: path) {
//        bitsX[i] = index & 1;
//        bitsY[i] = (index >> 1) & 1;
//        bitsZ[i] = (index >> 2) & 1;
//        i--;
//    }

//    pos.x = Origin::Utils::uintToFloat(bitsX.to_ullong());
//    pos.y = Origin::Utils::uintToFloat(bitsY.to_ullong());
//    pos.z = Origin::Utils::uintToFloat(bitsZ.to_ullong());

    return pos;
}

} // OctreeFarm

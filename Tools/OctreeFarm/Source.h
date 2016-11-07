#pragma once
#include <QObject>
#include <QColor>
#include <QSharedPointer>
#include <QVector>
#include <json/json.hpp>
#include <glm/glm.hpp>

struct Node;

using json = nlohmann::json;

class Source : public QObject {
    Q_OBJECT

public:
    explicit Source(QObject* parent = 0);
    void create(const QString& string = QString());
    QString serialize();
    QSharedPointer<QVector<uint32_t>> binary();
    bool changeNodeColor(const QVector<QSharedPointer<Node>>& selection, const QColor& color);
    bool changeNodeColor(const Node& node);
    bool deleteNode(const QVector<QSharedPointer<Node>>& selection);
    bool deleteNode(const Node& node);
    bool splitNode(const QVector<QSharedPointer<Node>>& selection);
    bool mergeNode(const QVector<QSharedPointer<Node>>& selection, Node& newNode, QVector<Node>& mergedNodes);
    bool mergeNode(const Node& node);
    bool addNode(const QVector<QSharedPointer<Node>>& selection, bool back, Node& newNode);
    bool addNode(const Node& node);
    void createChildren(const Node& node);

private:
    json::object_t* findNode(const QVector<int>& path, int index);
    QVector<int> posToPath(const glm::vec3& pos, int scale);
    glm::vec3 pathToPos(const QVector<int> path);

    json root;
    uint32_t defaultColor = 0xFF4681FF;
};

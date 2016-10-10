#pragma once
#include <QObject>
#include <QColor>
#include <QSharedPointer>
#include <QVector>
#include <QMap>
#include <json/json.hpp>
#include <glm/glm.hpp>

struct Node;

using json = nlohmann::json;

struct Property {
    json::object_t* parent;
    QString name;
    bool exist;
};

class Source : public QObject {
    Q_OBJECT

public:
    explicit Source(QObject* parent = 0);
    void create(const QString& string = QString());
    QString serialize();
    QSharedPointer<QVector<uint32_t>> binary();
    bool changeNodeColor(const QVector<QSharedPointer<Node>>& selection, const QColor& color);
    bool deleteNode(const QVector<QSharedPointer<Node>>& selection);
    bool splitNode(const QVector<QSharedPointer<Node>>& selection);
    bool mergeNode(const QVector<QSharedPointer<Node>>& selection);

private:
    json::object_t* findNode(const QVector<int>& path, int index);
    QVector<int> posToPath(const glm::uvec3& pos, int scale);

    json root;
    QMap<uint32_t, json::object_t*> parents;
    uint32_t defaultColor = 0xFF4681FF;
};

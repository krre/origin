#pragma once
#include <QObject>
#include <QColor>
#include <json/json.hpp>

using json = nlohmann::json;

class Source : public QObject {
    Q_OBJECT

public:
    explicit Source(QObject* parent = 0);
    void create(const QString& string = QString());
    QString serialize();
    QSharedPointer<QVector<uint32_t>> binary();

private:
    json root;
    uint32_t defaultColor = 0xFF4681FF;
};

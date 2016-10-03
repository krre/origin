#pragma once
#include <QObject>
#include <QJsonObject>
#include <QColor>

class Source : public QObject {
    Q_OBJECT

public:
    explicit Source(QObject* parent = 0);
    void create(const QString& string = QString());
    QString serialize();
    QSharedPointer<QVector<uint32_t>> binary();

private:
    QJsonObject root;
};

#include "Source.h"
#include <QtCore>

Source::Source(QObject* parent) : QObject(parent) {

}

void Source::create(const QString& string) {
    if (string.isEmpty()) {
        QJsonObject topNode;
        for (int i = 0; i < 8; i++) {
            QJsonObject node;
            node["color"] = QColor(Qt::blue).name(QColor::HexArgb);
            topNode[QString::number(i)] = node;
        }
        document.setObject(topNode);
    } else {
        document = QJsonDocument::fromJson(string.toUtf8());
    }
}

QString Source::serialize() {
    return QString(document.toJson());
}

QSharedPointer<QVector<uint32_t>> Source::binary() {
    QSharedPointer<QVector<uint32_t>> data;
    data.reset(new QVector<uint32_t>());
    data->append(0); // Header (at first empty)

    return data;
}

#include "Source.h"
#include <QtCore>

Source::Source(QObject* parent) : QObject(parent) {

}

void Source::create(const QString& string) {
    if (string.isEmpty()) {
        QJsonObject root;
        for (int i = 0; i < 8; i++) {
            QJsonObject node;
            node["color"] = QColor(Qt::blue).name(QColor::HexArgb);
            root[QString::number(i)] = node;
        }
    } else {
        root = QJsonDocument::fromJson(string.toUtf8()).object();
    }
}

QString Source::serialize() {
    QJsonDocument doc;
    doc.setObject(root);
    return QString(doc.toJson());
}

QSharedPointer<QVector<uint32_t>> Source::binary() {
    QSharedPointer<QVector<uint32_t>> data;
    data.reset(new QVector<uint32_t>());
    data->append(0); // Header (at first empty)

    return data;
}

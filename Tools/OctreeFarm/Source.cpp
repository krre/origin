#include "Source.h"
#include <QtCore>

Source::Source(QObject* parent) : QObject(parent) {

}

void Source::create(const QString& string) {
    if (string.isEmpty()) {
        for (int i = 0; i < 8; i++) {
            document.setObject(createNode(i, QColor(Qt::blue)));
        }

    } else {
        document = QJsonDocument::fromJson(string.toUtf8());
    }
}

QJsonObject Source::createNode(int index, const QColor& color) {
    QJsonObject node;
    node["idx"] = index;
    node["color"] = int(color.rgba());

    return node;
}

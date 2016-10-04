#include "Source.h"
#include <QtCore>

Source::Source(QObject* parent) : QObject(parent) {

}

void Source::create(const QString& string) {
    if (string.isEmpty()) {
        for (int i = 0; i < 8; i++) {
            json node;
            node["color"] = QColor(Qt::blue).name(QColor::HexArgb).toStdString();
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
    data->append(0); // Header (at first empty)

    json::object_t* parent = root.get_ptr<json::object_t*>();

    while (true) {

        uint32_t descriptor = 0;
        for (auto& node: (*parent)) {
            descriptor |= (1 << (8 + std::stoi(node.first)));

            json::iterator iter = node.second.find("children");
            if (iter != node.second.end()) {
                descriptor |= (1 << std::stoi(node.first));
            }

        }

        qDebug() << descriptor;

        break;


    }

    return data;
}

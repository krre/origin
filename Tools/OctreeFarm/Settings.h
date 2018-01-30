#pragma once
#include <QVariant>

class QString;
class QObject;

namespace OctreeFarm {

namespace Settings {

    void init(const QString filePath, QObject* parent);

    void beginGroup(const QString& prefix);
    void endGroup();

    void setValue(const QString& key, const QVariant& value);
    QVariant getValue(const QString& key, const QVariant& defaultValue = QVariant());

} // Settings

} // OctreeFarm

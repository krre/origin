#pragma once
#include <QVariant>

class QString;
class QObject;
class QSettings;

namespace OctreeFarm {

class Settings {

public:
    static void init(const QString filePath, QObject* parent);

    static void beginGroup(const QString& prefix);
    static void endGroup();

    static void setValue(const QString& key, const QVariant& value);
    static QVariant getValue(const QString& key, const QVariant& defaultValue = QVariant());
private:
    static QSettings* settings;
};

} // OctreeFarm

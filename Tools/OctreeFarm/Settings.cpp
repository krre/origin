#include "Settings.h"
#include <QSettings>

namespace OctreeFarm {

namespace Settings {

namespace {
    QSettings* settings;
}

void init(const QString filePath, QObject* parent) {
    settings = new QSettings(filePath, QSettings::IniFormat, parent);
}

void beginGroup(const QString& prefix) {
    settings->beginGroup(prefix);
}

void endGroup() {
    settings->endGroup();
}

void setValue(const QString& key, const QVariant& value) {
    settings->setValue(key, value);
}

QVariant getValue(const QString& key, const QVariant& defaultValue) {
    return settings->value(key, defaultValue);
}

} // Settings

} // OctreeFarm

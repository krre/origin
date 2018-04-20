#include "Settings.h"
#include <QSettings>

namespace OctreeFarm {

QSettings* Settings::settings = nullptr;

void Settings::init(const QString filePath, QObject* parent) {
    settings = new QSettings(filePath, QSettings::IniFormat, parent);
}

void Settings::beginGroup(const QString& prefix) {
    settings->beginGroup(prefix);
}

void Settings::endGroup() {
    settings->endGroup();
}

void Settings::setValue(const QString& key, const QVariant& value) {
    settings->setValue(key, value);
}

QVariant Settings::getValue(const QString& key, const QVariant& defaultValue) {
    return settings->value(key, defaultValue);
}

} // OctreeFarm

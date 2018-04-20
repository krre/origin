#include "Settings.h"
#include "Defines.h"
#include <QCoreApplication>

namespace OctreeFarm {

Settings::Settings() : QSettings(QCoreApplication::applicationDirPath() + "/" + APP_SETTINGS_NAME, QSettings::IniFormat)  {

}

} // OctreeFarm

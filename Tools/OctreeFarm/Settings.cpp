#include "Settings.h"
#include "Constants.h"
#include <QCoreApplication>

namespace OctreeFarm {

Settings::Settings() : QSettings(QCoreApplication::applicationDirPath() + "/" + Constants::App::SETTINGS_NAME, QSettings::IniFormat)  {

}

} // OctreeFarm

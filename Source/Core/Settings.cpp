#include "Settings.h"
#include "Application.h"
#include "Defines.h"
#include "Utils.h"
#include <experimental/filesystem>
#include <fstream>

namespace Origin {

namespace fs = std::experimental::filesystem;

Settings::Settings() {
    path = Application::getCurrentDirectory() + Utils::getPathSeparator() + APP_SETTINGS_NAME;
    if (fs::exists(path)) {
        std::string text = Utils::readTextFile(path);
        storage = json::parse(text);
    } else {
        setDefaultSettings();
    }
}

Settings::~Settings() {
    saveAll();
}

void Settings::saveAll() {
    std::ofstream out(path);
    std::string text = storage.dump(4);
    out << text;
    out.close();
}

void Settings::setDefaultSettings() {
}

} // Origin

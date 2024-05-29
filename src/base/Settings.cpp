#include "Settings.h"
#include "Game.h"
#include <core/Utils.h>
#include <fstream>

Settings::Settings(Object* parent) : SingleObject(parent) {
    path = Game::getCurrentDirectory() + Core::Utils::getPathSeparator() + Game::SettingsName;
    if (std::filesystem::exists(path)) {
        std::string text = Core::Utils::readTextFile(path);
        storage = json::parse(text);
    } else {
        setDefaultSettings();
    }
}

Settings::~Settings() {
    saveAll();
}

void Settings::saveAll() {
    std::ofstream out(get()->path);
    out << get()->storage.dump(4);
    out.close();
}

void Settings::setDefaultSettings() {
}

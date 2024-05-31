#include "Settings.h"
#include "Game.h"
#include <core/Utils.h>
#include <fstream>

Settings::Settings(Object* parent) : SingleObject(parent) {
    path = Game::currentDirectory() + Core::Utils::getPathSeparator() + Game::SettingsName;
    if (std::filesystem::exists(path)) {
        std::string text = Core::Utils::readTextFile(path);
        m_storage = json::parse(text);
    } else {
        setDefaultSettings();
    }
}

Settings::~Settings() {
    saveAll();
}

void Settings::saveAll() {
    std::ofstream out(get()->path);
    out << get()->m_storage.dump(4);
    out.close();
}

void Settings::setDefaultSettings() {
}

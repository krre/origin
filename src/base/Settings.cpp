#include "Settings.h"
#include "Game.h"
#include <core/Utils.h>
#include <fstream>

Settings::Settings(Object* parent) : SingleObject(parent) {
    m_path = Game::currentDirectory() + Core::Utils::pathSeparator() + Game::SettingsName;
    if (std::filesystem::exists(m_path)) {
        std::string text = Core::Utils::readTextFile(m_path);
        m_storage = json::parse(text);
    } else {
        setDefaultSettings();
    }
}

Settings::~Settings() {
    saveAll();
}

void Settings::saveAll() {
    std::ofstream out(get()->m_path);
    out << get()->m_storage.dump(4);
    out.close();
}

void Settings::setDefaultSettings() {
}

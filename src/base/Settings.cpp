#include "Settings.h"
#include "Game.h"
#include "Constants.h"
#include "core/Utils.h"
#include <fstream>

Settings::Settings(Object* parent) : SingleObject(parent) {
    path = Game::getCurrentDirectory() + Core::Utils::getPathSeparator() + Constants::App::SETTINGS_NAME;
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

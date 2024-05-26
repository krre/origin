#include "Settings.h"
#include "Game.h"
#include "Constants.h"
#include "Core/Utils.h"
#include <experimental/filesystem>
#include <fstream>

namespace fs = std::experimental::filesystem;

Settings::Settings(Object* parent) : SingleObject(parent) {
    path = Game::getCurrentDirectory() + Core::Utils::getPathSeparator() + Constants::App::SETTINGS_NAME;
    if (fs::exists(path)) {
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

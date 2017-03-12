#include "Settings.h"
#include "App.h"
#include "Utils.h"
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

Settings::Settings(const std::string& name) {
    path = App::getCurrentPath() + Utils::getPathSeparator() + name;
    if (fs::exists(path)) {
        PRINT("Load settings")
    }
}

Settings::~Settings() {
    saveAll();
}

void Settings::saveAll() {
    PRINT("Save all")
}

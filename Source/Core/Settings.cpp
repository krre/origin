#include "Settings.h"
#include "App.h"
#include "Defines.h"
#include "Utils.h"
#include <experimental/filesystem>
#include <fstream>

namespace fs = std::experimental::filesystem;

Settings::Settings() {
    path = App::getCurrentPath() + Utils::getPathSeparator() + APP_SETTINGS_NAME;
    if (fs::exists(path)) {
        std::string text = Utils::readTextFile(path);
        std::stringstream stream(text);
        std::string line;

        while (std::getline(stream, line, '\n')) {
            line.erase(remove_if(line.begin(), line.end(), isspace), line.end());

            if (line.size()) {
                std::vector<std::string> pair = Utils::split(line, '=');
                if (pair.size() != 2) {
                    throw std::runtime_error("Failed to parse settings file at line: " + line);
                } else {
                    storage[pair.at(0)] = pair.at(1);
                }
            }
        }
    } else {
        setDefaultSettings();
    }
}

Settings::~Settings() {
    saveAll();
}

void Settings::setValue(const std::string& name, const std::string& value) {
    storage[name] = value;
}

std::string Settings::getValue(const std::string& name) {
    const auto it = storage.find(name);
    if (it != storage.end()) {
        return it->second;
    } else {
        return std::string();
    }
}

void Settings::saveAll() {
    std::ofstream out(path);
    std::string line;
    for (const auto& it : storage) {
        line = it.first + " = " + it.second + "\n";
        out << line;
    }
    out.close();
}

void Settings::setDefaultSettings() {
}

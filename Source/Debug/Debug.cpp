#include "Debug.h"
#include "../Core/App.h"
#include "../Core/Utils.h"
#include "../Scene/SceneManager.h"
#include "../Scene/MenuScene.h"
#include "../Scene/SettingsScene.h"
#include "../Scene/WorldScene.h"
#include <Origin.h>

Debug::Debug() {
#ifdef DEVELOP_MODE
    loadValues();
#endif
}

void Debug::setValue(const std::string& key, const std::string& value) {
    values[key] = value;
}

std::string Debug::getValue(const std::string& key) const {
    return values.at(key);
}

void Debug::setDebugScene() {
    std::string sceneName = values["scene"];
    if (sceneName.size()) {
        if (sceneName == "menu") {
            SceneManager::get()->setScene(std::make_shared<MenuScene>());
        } else if (sceneName == "settings") {
            SceneManager::get()->setScene(std::make_shared<SettingsScene>());
        } else if (sceneName == "world") {
            SceneManager::get()->setScene(std::make_shared<WorldScene>());
        }
    } else {
        SceneManager::get()->setScene(std::make_shared<MenuScene>());
    }
}

void Debug::loadValues() {
    std::string mainDebugPath = App::getCurrentPath() + "/Debug/main.debug";
    std::string mainDebugText = Utils::readTextFile(mainDebugPath);
    std::stringstream stream(mainDebugText);
    std::string line;

    while (std::getline(stream, line, '\n')) {
        line.erase(remove_if(line.begin(), line.end(), isspace), line.end());

        // Ignore empty strings and strings with first '#' symbol
        if (line.size() && line.at(0) != '#') {
            std::vector<std::string> pair = Utils::split(line, '=');
            if (pair.size() != 2) {
                ERROR("Failed to parse main.debug at line: " << line);
            } else {
                values[pair.at(0)] = pair.at(1);
            }
        }
    }

    for (auto value : values) {
        if (value.first == "enable") {
            enable = value.second == "true";
        }
    }
}

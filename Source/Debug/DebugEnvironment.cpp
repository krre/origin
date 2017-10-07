#include "DebugEnvironment.h"
#include "Core/App.h"
#include "Core/Defines.h"
#include "Core/Utils.h"
#include "Scene/SceneManager.h"
#include "Scene/Menu/MenuScene.h"
#include "Scene/Settings/SettingsScene.h"
#include "Scene/World/WorldScene.h"
#include "Debug/DebugHUD.h"

DebugEnvironment::DebugEnvironment() {
#ifdef DEVELOP_MODE
    loadValues();
#endif
}

void DebugEnvironment::setValue(const std::string& key, const std::string& value) {
    values[key] = value;
}

std::string DebugEnvironment::getValue(const std::string& key) const {
    if (values.find(key) != values.end()) {
        return values.at(key);
    } else {
        return std::string();
    }
}

void DebugEnvironment::setDebugScene() {
    const std::string& sceneName = getValue("scene");
    if (!sceneName.empty()) {
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

    if (getValue("debugHUD") == "true") {
//        DebugHUD::get()->setVisible(true);
    }
}

void DebugEnvironment::loadValues() {
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
                throw std::runtime_error("Failed to parse main.debug at line: " + line);
            } else {
                values[pair.at(0)] = pair.at(1);
            }
        }
    }

    enable = getValue("enable") == "true";
}

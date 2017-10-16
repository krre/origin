#include "DebugEnvironment.h"
#include "Core/Application.h"
#include "Core/Game.h"
#include "Core/Defines.h"
#include "Core/Utils.h"
#include "Debug/DebugHUD.h"
#include "Screen/MenuScreen.h"

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

void DebugEnvironment::setDebugScreen() {
    const std::string& screenName = getValue("screen");
    if (!screenName.empty()) {
        if (screenName == "menu") {
            Game::get()->setScreen(std::make_shared<MenuScreen>());
        } else if (screenName == "settings") {
//            Game::get()->setScreen(std::make_shared<SettingsScreen>());
        } else if (screenName == "world") {
//            Game::get()->setScreen(std::make_shared<WorldScreen>());
        }
    } else {
        Game::get()->setScreen(std::make_shared<MenuScreen>());
    }

    if (getValue("debugHUD") == "true") {
//        DebugHUD::get()->setVisible(true);
    }
}

void DebugEnvironment::loadValues() {
    std::string mainDebugPath = Application::getCurrentPath() + "/Debug/main.debug";
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

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

void DebugEnvironment::setDebugScreen() {
    const std::string& screenName = mainSettings["screen"];
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
}

void DebugEnvironment::loadValues() {
    std::string mainPath = Application::getCurrentPath() + "/Debug/main.json";
    std::string mainText = Utils::readTextFile(mainPath);
    mainSettings = json::parse(mainText);

    enable = mainSettings["enable"];

    std::string vulkanPath = Application::getCurrentPath() + "/Debug/vulkan.json";
    std::string vulkanText = Utils::readTextFile(vulkanPath);
    vulkanSettings = json::parse(vulkanText);
}

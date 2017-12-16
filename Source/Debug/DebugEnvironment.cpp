#include "DebugEnvironment.h"
#include "Core/Application.h"
#include "Core/Defines.h"
#include "Core/Utils.h"
#include "Debug/DebugHUD.h"
#include "Screen/MenuScreen.h"
#include "Graphics/Render/RenderWindow.h"

DebugEnvironment::DebugEnvironment() {
#ifdef DEVELOP_MODE
    loadValues();
#endif
}

void DebugEnvironment::setDebugScreen() {
    uint32_t s = settings["general"]["screen"];
    Screens screen = static_cast<Screens>(s);
    Size size(Application::get()->getWindow()->getWidth(), Application::get()->getWindow()->getHeight());
    if (screen == Screens::MENU) {
        Application::get()->getWindow()->setScreen(std::make_shared<MenuScreen>(size));
    } else if (screen == Screens::SETTINGS) {
//        Application::get()->getWindow()->setScreen(std::make_shared<SettingsScreen>());
    } else if (screen == Screens::GAME) {
//        Application::get()->getWindow()->setScreen(std::make_shared<WorldScreen>());
    }
}

void DebugEnvironment::loadValues() {
    std::string filePath = Application::getCurrentPath() + "/debug.json";
    try {
        std::string text = Utils::readTextFile(filePath);
        settings = json::parse(text);
        enable = settings["general"]["enable"];
    } catch (const std::exception& ex) {
        ERROR(ex.what())
    };
}

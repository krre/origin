#include "DebugEnvironment.h"
#include "Core/Application.h"
#include "Core/Defines.h"
#include "Core/Utils.h"
#include "Debug/DebugHUD.h"
#include "Screen/MenuScreen.h"
#include "Core/Window.h"

namespace Origin {

DebugEnvironment::DebugEnvironment() {
#ifdef DEVELOP_MODE
    loadValues();
#endif
}

GraphicsBackend DebugEnvironment::getGraphicsBackend() const {
    uint8_t s = settings["general"]["backend"];
    return static_cast<GraphicsBackend>(s);
}

void DebugEnvironment::setDebugScreen() {
    uint8_t s = settings["general"]["screen"];
    Screen::Name screen = static_cast<Screen::Name>(s);
    if (screen == Screen::Name::Menu) {
        Application::get()->getWindow()->setScreen(std::make_shared<MenuScreen>());
    } else if (screen == Screen::Name::Settings) {
//        Application::get()->getWindow()->setScreen(std::make_shared<SettingsScreen>());
    } else if (screen == Screen::Name::Game) {
//        Application::get()->getWindow()->setScreen(std::make_shared<WorldScreen>());
    }
}

void DebugEnvironment::loadValues() {
    std::string filePath = Application::getCurrentDirectory() + "/debug.json";
    try {
        std::string text = Utils::readTextFile(filePath);
        settings = json::parse(text);
        enable = settings["general"]["enable"];
    } catch (const std::exception& ex) {
        ERROR(ex.what())
    };
}

} // Origin

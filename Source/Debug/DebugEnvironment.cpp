#include "DebugEnvironment.h"
#include "Core/Application.h"
#include "Core/Defines.h"
#include "Core/Utils.h"
#include "Debug/DebugHUD.h"
#include "Screen/MenuScreen.h"
#include "Graphics/Render/RenderWindow.h"

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
    GameScreen screen = static_cast<GameScreen>(s);
    if (screen == GameScreen::MENU) {
        Application::get()->getWindow()->setScreen(std::make_shared<MenuScreen>());
    } else if (screen == GameScreen::SETTINGS) {
//        Application::get()->getWindow()->setScreen(std::make_shared<SettingsScreen>());
    } else if (screen == GameScreen::GAME) {
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

} // Origin

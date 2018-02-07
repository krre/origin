#include "DebugEnvironment.h"
#include "Core/Game.h"
#include "Core/Defines.h"
#include "Core/Utils.h"
#include "Debug/DebugHUD.h"
#include "Screen/MenuScreen.h"
#include "Screen/SettingsScreen.h"
#include "Screen/GameScreen.h"
#include "Core/Window.h"

namespace Origin {

DebugEnvironment::DebugEnvironment() {
#ifdef DEVELOP_MODE
    loadValues();
#endif
}

void DebugEnvironment::setDebugScreen() {
    uint8_t s = settings["general"]["screen"];
    Screen::Name screen = static_cast<Screen::Name>(s);
    if (screen == Screen::Name::Menu) {
        Game::getWindow()->setScreen(std::make_shared<MenuScreen>());
    } else if (screen == Screen::Name::Settings) {
        Game::getWindow()->setScreen(std::make_shared<SettingsScreen>());
    } else if (screen == Screen::Name::Game) {
        Game::getWindow()->setScreen(std::make_shared<GameScreen>());
    }
}

void DebugEnvironment::loadValues() {
    std::string filePath = Game::getCurrentDirectory() + "/debug.json";
    try {
        std::string text = Utils::readTextFile(filePath);
        settings = json::parse(text);
        enable = settings["general"]["enable"];
    } catch (const std::exception& ex) {
        PRINT(ex.what())
    };
}

} // Origin

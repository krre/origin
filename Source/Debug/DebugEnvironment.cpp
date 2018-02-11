#include "DebugEnvironment.h"
#include "Core/Game.h"
#include "Core/Defines.h"
#include "Core/Utils.h"
#include "Debug/DebugHUD.h"
#include "Screen/MenuScreen.h"
#include "Screen/SettingsScreen.h"
#include "Screen/GameScreen.h"
#include "Screen/NewWorldScreen.h"
#include "Screen/LoadWorldScreen.h"
#include "Core/Window.h"

namespace Origin {

DebugEnvironment::DebugEnvironment(Object* parent) : Object(parent) {
#ifdef DEVELOP_MODE
    loadValues();
#endif
}

void DebugEnvironment::setDebugScreen() {
    uint8_t s = settings["general"]["screen"];
    Screen::Name screen = static_cast<Screen::Name>(s);
    switch (screen) {
        case Screen::Name::Menu:
            Game::getWindow()->setScreen(std::make_shared<MenuScreen>());
            break;
        case Screen::Name::Settings:
            Game::getWindow()->setScreen(std::make_shared<SettingsScreen>());
            break;
        case Screen::Name::Game:
            Game::getWindow()->setScreen(std::make_shared<GameScreen>("test"));
            break;
        case Screen::Name::NewGame:
            Game::getWindow()->setScreen(std::make_shared<NewWorldScreen>());
            break;
        case Screen::Name::LoadGame:
            Game::getWindow()->setScreen(std::make_shared<LoadWorldScreen>());
            break;
        default:
            assert(0 && "Screen not found");
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

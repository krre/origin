#include "Game.h"
#include "Application.h"
#include "Defines.h"
#include "Graphics/Render/RenderWindow.h"
#include "Utils.h"
#include "Debug/DebugHUD.h"
#include "Debug/DebugEnvironment.h"
#include "Screen/MenuScreen.h"
#include "UI/Toast.h"
#include "Event/Event.h"
#include "Event/Input.h"
#include <SDL_keycode.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <ctime>
#include <lodepng/lodepng.h>
#include <experimental/filesystem>

Game::Game() {
    if (DebugEnvironment::get()->getEnable()) {
        DebugEnvironment::get()->setDebugScreen();
    } else {
        Size size(Application::get()->getWindow()->getWidth(), Application::get()->getWindow()->getHeight());
        setScreen(std::make_shared<MenuScreen>(size));
    }

    Event::get()->keyPressed.connect<Game, &Game::onKeyPressed>(this);
}

void Game::pushScreen(const std::shared_ptr<Screen>& screen) {
    if (!screens.empty()) {
        screens.back()->pause();
    }
    screens.push_back(screen);
    screen->resume();
}

void Game::popScreen() {
    if (screens.size() > 1) {
        screens.back()->pause();
        screens.pop_back();
        screens.back()->resume();
    } else {
        // TODO: Question dialog about exit from game
        PRINT("Exit question dialog")
    }
}

void Game::setScreen(const std::shared_ptr<Screen>& screen) {
    for (const auto& screen : screens) {
        screen->pause();
    }
    screens.clear();
    pushScreen(screen);
}

void Game::update(float dt) {
    screens.back()->update(dt);
}

void Game::render() {
    screens.back()->render();
}

void Game::load() {

}

void Game::save() {

}

void Game::resize(uint32_t width, uint32_t height) {
    for (const auto& screen : screens) {
        screen->resize(width, height);
    }
}

void Game::onKeyPressed(const SDL_KeyboardEvent& event) {
    switch (event.keysym.sym) {
#ifdef DEBUG_HUD_ENABLE
    case SDLK_F5:
        DebugHUD::get()->trigger();
        break;
#endif
    case SDLK_F10:
        Application::get()->getWindow()->toggleFullScreen();
        break;
    case SDLK_F11:
        saveScreenshot();
        break;
    }
}

void Game::saveScreenshot() {
    std::string directoryPath = Application::getCurrentPath() + Utils::getPathSeparator() + "Screenshot";
    namespace fs = std::experimental::filesystem;
    if (!fs::exists(directoryPath)) {
        fs::create_directory(directoryPath);
    }

    time_t t = std::time(0); // Get time now
    struct tm* now = std::localtime(&t);
    std::string filename =
            std::to_string(now->tm_year + 1900) + "-" +
            Utils::zeroFill(std::to_string(now->tm_mon + 1)) + "-" +
            Utils::zeroFill(std::to_string(now->tm_mday)) + "_" +
            Utils::zeroFill(std::to_string(now->tm_hour)) + "-" +
            Utils::zeroFill(std::to_string(now->tm_min)) + "-" +
            Utils::zeroFill(std::to_string(now->tm_sec)) + ".png";
    std::string filePath = directoryPath + Utils::getPathSeparator() + filename;

    Application::get()->getWindow()->saveImage(filePath);

    std::string message = "Screenshot saved to " + filename;
//    Toast::get()->showToast(message);
    PRINT(message)
}

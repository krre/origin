#include "Game.h"
#include "App.h"
#include "GameWindow.h"
#include "Utils.h"
#include "Scene/World/WorldScene.h"
#include "Debug/DebugHUD.h"
#include "Debug/DebugEnvironment.h"
#include "UI/Toast.h"
#include "Event/Event.h"
#include "Event/Input.h"
#include "Scene/SceneManager.h"
#include "Scene/Menu/MenuScene.h"
#include "Graphics/Vulkan/Swapchain.h"
#include "Graphics/Vulkan/Instance.h"
#include "Graphics/Vulkan/Surface.h"
#include <Origin.h>
#include <SDL_keycode.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <ctime>
#include <lodepng/lodepng.h>
#include <experimental/filesystem>

Game::Game() {
    if (DebugEnvironment::get()->getEnable()) {
        DebugEnvironment::get()->setDebugScene();
    } else {
        SceneManager::get()->setScene(std::make_shared<MenuScene>());
    }

    Event::get()->keyPressed.connect<Game, &Game::onKeyPressed>(this);
}

void Game::load() {

}

void Game::save() {

}

void Game::setWorldScene(WorldScene* worldScene) {
    this->worldScene = worldScene;
}

void Game::onKeyPressed(const SDL_KeyboardEvent& event) {
    switch (event.keysym.sym) {
#ifdef DEBUG_HUD_ENABLE
    case SDLK_F5:
        DebugHUD::get()->trigger();
        break;
#endif
    case SDLK_F10:
        // TODO: Incorrect work
        toggleFullScreen();
        break;
    case SDLK_F11:
        saveScreenshot();
        break;
    }
}

void Game::toggleFullScreen() {
    bool isFullscreen = SDL_GetWindowFlags(App::get()->getWindow()->getHandle()) & SDL_WINDOW_FULLSCREEN;
    SDL_SetWindowFullscreen(App::get()->getWindow()->getHandle(), isFullscreen ? 0 : SDL_WINDOW_FULLSCREEN);
    SDL_ShowCursor(isFullscreen);
}

void Game::saveScreenshot() {
    std::string directoryPath = App::getCurrentPath() + Utils::getPathSeparator() + "Screenshot";
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

    Vulkan::Instance::get()->getSurface()->getSwapchain()->saveImage(filePath);

    std::string message = "Screenshot saved to " + filename;
//    Toast::get()->showToast(message);
    PRINT(message)
}

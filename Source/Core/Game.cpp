#include "Game.h"
#include "App.h"
#include "Utils.h"
#include "../Debug/Console.h"
#include "../Debug/DebugHUD.h"
#include "../UI/Toast.h"
#include "../Event/Event.h"
#include "../Event/Input.h"
#include "../GameState/GameStateManager.h"
#include <SDL_keycode.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <ctime>
#include <lodepng/lodepng.h>
#include <Gagarin.h>
#include <experimental/filesystem>

Game::Game() {
#ifdef DEVELOP_MODE
    loadDevelopSettings();
#endif

    GameStateManager::get()->setState(GameState::MENU);
}

void Game::load() {

}

void Game::save() {

}

void Game::onKeyPressed(const SDL_KeyboardEvent& event) {
    GameState::Type gameState = GameStateManager::get()->getStateType();
    switch (event.keysym.sym) {
    case SDLK_ESCAPE:
        if (Input::get()->isKeyAccepted) break;
        if (gameState == GameState::PLAY) {
            GameStateManager::get()->pushState(GameState::PAUSE);
        } else if (gameState == GameState::CONSOLE) {
//            MovementControllerSystem* movementControllerSystem = static_cast<MovementControllerSystem*>(Engine::get()->getSystem(SystemType::MovementController).get());
//            movementControllerSystem->setActive(true);
            Console::get()->setVisible(false);
            GameStateManager::get()->popState();
        }
        break;
#ifdef DEBUG_HUD_ENABLE
    case SDLK_F5:
        DebugHUD::get()->trigger();
        break;
#endif
    case SDLK_F10:
        // TODO: Incorrect work
//        toggleFullScreen();
        break;

    case SDLK_F12:
        saveScreenshot();
        break;
#ifdef CONSOLE_ENABLE
    case SDLK_SLASH:
        if (gameState == GameState::PLAY) {
//            MovementControllerSystem* movementControllerSystem = static_cast<MovementControllerSystem*>(Engine::get()->getSystem(SystemType::MovementController).get());
//            movementControllerSystem->setActive(false);
            Console::get()->setVisible(true);
            GameStateManager::get()->pushState(GameState::CONSOLE);
        }
        break;
#endif
#ifdef DEVELOP_MODE
    case SDLK_KP_0:
//        App::get()->getViewport()->switchCamera();
        break;
#endif
    default:
        break;
    }
}

void Game::toggleFullScreen() {
    bool isFullscreen = SDL_GetWindowFlags(App::get()->getWindow()) & SDL_WINDOW_FULLSCREEN;
    SDL_SetWindowFullscreen(App::get()->getWindow(), isFullscreen ? 0 : SDL_WINDOW_FULLSCREEN);
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

    int width = App::get()->getWidth();
    int height = App::get()->getHeight();

    unsigned char* image = new unsigned char[width * height * 4];
//    glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, image);

    // Vertically flip
    for (unsigned y = 0; y < height / 2; y++) {
        unsigned swapY = height - y - 1;
        for(unsigned x = 0; x < width; x++) {
            unsigned offset = 4 * (x + y * width);
            unsigned swapOffset = 4 * (x + swapY * width);
            unsigned char temp;

            for (int channel = 0; channel <= 3; channel++ ) {
                temp = image[offset + channel];
                image[offset + channel] = image[swapOffset + channel];
                image[swapOffset + channel] = temp;
            }
        }
    }

    lodepng::encode(filePath, image, width, height);

    delete[] image;

    std::string message = "Screenshot saved to " + filename;
    Toast::get()->showToast(message);
}

void Game::loadDevelopSettings() {
    std::string mainDebugPath = App::getCurrentPath() + "/Debug/main.debug";
    std::string mainDebugText = Utils::readTextFile(mainDebugPath);
    std::stringstream stream(mainDebugText);
    std::string line;

    while (std::getline(stream, line, '\n')) {
//        print(line)
    }
}

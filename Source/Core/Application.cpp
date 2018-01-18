#include "Application.h"
#include "SDLWrapper.h"
#include "Game.h"
#include "Utils.h"
#include "Defines.h"
#include "Event/Event.h"
#include "Event/Input.h"
#include "Resource/ResourceManager.h"
#include "Debug/Logger.h"
#include "Debug/DebugEnvironment.h"
#include "Debug/DebugHUD.h"
#include "Core/Settings.h"
#include "Graphics/Render/RenderEngine.h"
#include "Window.h"
#include "Screen/MenuScreen.h"
#include <string>
#include <SDL_timer.h>
#include <algorithm>
#include <experimental/filesystem>

namespace Origin {

Application::Application(int argc, char* argv[]) {
    for (int i = 0; i < argc; i++) {
        this->argv.push_back(argv[i]);
    }

    init();
}

Application::~Application() {
    Game::release();
    Input::release();
//    DebugHUD::release();
    ResourceManager::release();
    window.reset();
    RenderEngine::release();
    SDLWrapper::shutdown();
    Event::release();
    DebugEnvironment::release();
    Logger::release();
    Settings::release();
}

std::string Application::getCurrentDirectory() {
    return std::experimental::filesystem::current_path().string();
}

void Application::init() {
    try {
        // Order is important
        new Settings;
        new Logger;
        new DebugEnvironment;
        new Event;

        SDLWrapper::init();
        window = std::make_unique<Window>();

        new RenderEngine;
        new ResourceManager;
//        new DebugHUD;
        new Input;
        new Game;
    } catch (const std::exception& ex) {
        if (SDLWrapper::isInited()) {
            SDLWrapper::showErrorMessageBox(ex.what());
        } else {
            ERROR(ex.what());
        }
    }

    if (DebugEnvironment::get()->getEnable()) {
        DebugEnvironment::get()->setDebugScreen();
    } else {
        window->setScreen(std::make_shared<MenuScreen>());
    }

    Event::get()->quit.connect(this, &Application::quit);

    window->onResize(window->getWidth(), window->getHeight());
    window->show();

    running = true;
}

void Application::run() {
    Uint64 frequency = SDL_GetPerformanceFrequency();
    Uint64 currentTime = SDL_GetPerformanceCounter();

    while (running) {
        Event::get()->handleEvents();

        Uint64 newTime = SDL_GetPerformanceCounter();
        double frameTime = double(newTime - currentTime) / frequency;
        currentTime = newTime;

        window->update(frameTime);
        window->render();
//        PRINT(frameTime << " " << 1 / frameTime)
    }
}

void Application::quit() {
    running = false;
}

} // Origin

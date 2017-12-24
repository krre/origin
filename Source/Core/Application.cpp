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
#include "Graphics/Render/RendererSet.h"
#include "Graphics/Render/RenderWindow.h"
#include "Graphics/Render/RenderManager.h"
#include "Graphics/Vulkan/Context.h"
#include "Graphics/Vulkan/Instance.h"
#include "Screen/MenuScreen.h"
#include <string>
#include <SDL_timer.h>
#include <algorithm>
#include <experimental/filesystem>

Application::Application(int argc, char* argv[]) {
    for (int i = 0; i < argc; i++) {
        this->argv.push_back(argv[i]);
    }

    init();
}

Application::~Application() {
    Game::release();
    Input::release();
    DebugHUD::release();
    ResourceManager::release();
    RendererSet::release();
    RenderManager::release();
    window.reset();
    Vulkan::Context::release();
    SDLWrapper::release();
    Event::release();
    DebugEnvironment::release();
    Logger::release();
    Settings::release();
}

std::string Application::getCurrentPath() {
    return std::experimental::filesystem::current_path().string();
}

void Application::init() {
    try {
        // Order is important
        new Settings;
        new Logger;
        new DebugEnvironment;
        new Event;

        new SDLWrapper;
        SDLWrapper::get()->init();

        if (DebugEnvironment::get()->getEnable()) {
            Vulkan::ContextProperties properties = {};

            if (DebugEnvironment::get()->getSettings()["vulkan"]["layers"]["use"]) {
                properties.useLayers = true;
                for (auto& layer : DebugEnvironment::get()->getSettings()["vulkan"]["layers"]["list"]) {
                    properties.layers.push_back(layer);
                }
            }

            if (DebugEnvironment::get()->getSettings()["vulkan"]["extensions"]["use"]) {
                properties.useExtensions = true;
                for (auto& layer : DebugEnvironment::get()->getSettings()["vulkan"]["extensions"]["list"]) {
                    properties.extensions.push_back(layer);
                }
            }

            new Vulkan::Context(properties);
        } else {
            new Vulkan::Context;
        }

        window = std::make_unique<RenderWindow>();

        new ResourceManager;
        new RenderManager;
        new RendererSet;
        new DebugHUD;
        new Input;
        new Game;
    } catch (const std::exception& ex) {
        if (SDLWrapper::exists() && SDLWrapper::get()->isInited()) {
            SDLWrapper::get()->showErrorMessageBox(ex.what());
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

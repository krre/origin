#include "Game.h"
#include "SDLWrapper.h"
#include "Core/Utils.h"
#include "Core/Defines.h"
#include "Defines.h"
#include "Event/Event.h"
#include "Event/Input.h"
#include "Resource/ResourceManager.h"
#include "Debug/Logger.h"
#include "Debug/DebugEnvironment.h"
#include "UI/Overlay.h"
#include "UI/UIManager.h"
#include "Graphics/Render/RenderManager.h"
#include "Graphics/Render/SceneRenderer.h"
#include "Graphics/Render/DebugRenderer.h"
#include "Graphics/Render/UIRenderer.h"
#include "ECS/EntityManager.h"
#include "Base/Settings.h"
#include "Window.h"
#include "Screen/MenuScreen.h"
#include "World/World.h"
#include <string>
#include <algorithm>
#include <memory>
#include <experimental/filesystem>
#include <SDL.h>

bool Game::running = false;

Game::Game(int argc, char* argv[], Object* parent) : Object(parent) {
    for (int i = 0; i < argc; i++) {
        argvs.push_back(argv[i]);
    }

    init();
}

Game::~Game() {
    SDL::shutdown();
    ResourceManager::get()->cleanup();
}

void Game::init() {
    try {
        SDL::init();
        new Settings(this);
        new Logger(this);
        new DebugEnvironment(this);
        new Event(this);
        new Window(this);
        new ResourceManager(this);

        SDL::Platform platform = SDL::getPlatform(Window::get()->getHandle());
        new RenderManager(platform.handle, platform.window);

        if (DebugEnvironment::getEnable()) {
            if (DebugEnvironment::getSettings()["vulkan"]["debugReport"]["use"]) {
                RenderManager::get()->useDebugReport(DebugEnvironment::getVulkanDebugReportFlags());
            }

            if (DebugEnvironment::getSettings()["vulkan"]["layers"]["use"]) {
                RenderManager::get()->setEnabledLayers(DebugEnvironment::getSettings()["vulkan"]["layers"]["list"]);
            }

            if (DebugEnvironment::getSettings()["vulkan"]["extensions"]["use"]) {
                RenderManager::get()->setEnabledExtensions(DebugEnvironment::getSettings()["vulkan"]["extensions"]["list"]);
            }

            RenderManager::get()->setDeviceIndex(DebugEnvironment::getVulkanDevice());
        }
        RenderManager::get()->create();

        RenderManager::get()->addRenderer(new SceneRenderer(this));
        RenderManager::get()->addRenderer(new DebugRenderer(this));
        RenderManager::get()->addRenderer(new UIRenderer(this));

        new UIManager(this);
        new EntityManager(this);
        new Overlay();
        Overlay::get()->setParent(this);

        if (DebugEnvironment::getEnable() && DebugEnvironment::getSettings()["general"]["debugHud"]) {
            Overlay::get()->toggleDebugHUD();
        }

        new Input(this);
        new World(this);
    } catch (const std::exception& ex) {
        if (SDL::isInited()) {
            SDL::showErrorMessageBox(ex.what());
        } else {
            PRINT(ex.what());
        }
    }

    if (DebugEnvironment::getEnable()) {
        DebugEnvironment::setDebugScreen();
    } else {
        Window::get()->setScreen(std::make_shared<MenuScreen>());
    }

    Window::get()->onResize(Window::get()->getWidth(), Window::get()->getHeight());
    Window::get()->show();

    running = true;
}

void Game::run() {
    Uint64 frequency = SDL_GetPerformanceFrequency();
    Uint64 currentTime = SDL_GetPerformanceCounter();

    while (running) {
        Event::get()->handleEvents();
        Window::get()->invokeDeffered();
        Overlay::get()->invokeDeffered();

        Uint64 newTime = SDL_GetPerformanceCounter();
        double frameTime = double(newTime - currentTime) / frequency;
        currentTime = newTime;

        Window::get()->update(frameTime);
        Window::get()->render();
//        PRINT(frameTime << " " << 1 / frameTime)
    }

    Window::get()->close();
}

void Game::quit() {
    running = false;
}

std::string Game::getCurrentDirectory() {
    return std::experimental::filesystem::current_path().string();
}

bool Game::isRunning() {
    return running;
}

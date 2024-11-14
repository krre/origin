#include "Game.h"
#include "SDLWrapper.h"
#include "event/Event.h"
#include "event/Input.h"
#include "resource/ResourceManager.h"
#include "debug/Logger.h"
#include "debug/DebugEnvironment.h"
#include "ui/Overlay.h"
#include "ui/UIManager.h"
#include "graphics/render/RenderManager.h"
#include "graphics/render/SceneRenderer.h"
#include "graphics/render/DebugRenderer.h"
#include "graphics/render/UIRenderer.h"
#include "ecs/EntityManager.h"
#include "base/Settings.h"
#include "Window.h"
#include "screen/MenuScreen.h"
#include "world/World.h"
#include <string>
#include <memory>
#include <SDL.h>

bool Game::s_running = false;

Game::Game(int argc, char* argv[], Object* parent) : Object(parent) {
    for (int i = 0; i < argc; i++) {
        m_args.push_back(argv[i]);
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

        SDL::Platform platform = SDL::platform(Window::get()->handle());
        new RenderManager(platform.handle, platform.window);

        if (DebugEnvironment::enabled()) {
            if (DebugEnvironment::settings()["vulkan"]["debugReport"]["use"]) {
                RenderManager::get()->useDebugReport(DebugEnvironment::vulkanDebugReportFlags());
            }

            if (DebugEnvironment::settings()["vulkan"]["layers"]["use"]) {
                RenderManager::get()->setEnabledLayers(DebugEnvironment::settings()["vulkan"]["layers"]["list"]);
            }

            if (DebugEnvironment::settings()["vulkan"]["extensions"]["use"]) {
                RenderManager::get()->setEnabledExtensions(DebugEnvironment::settings()["vulkan"]["extensions"]["list"]);
            }

            RenderManager::get()->setDeviceIndex(DebugEnvironment::vulkanDevice());
        }

        RenderManager::get()->create();
        RenderManager::get()->addRenderer(new SceneRenderer(this));
        RenderManager::get()->addRenderer(new DebugRenderer(this));
        RenderManager::get()->addRenderer(new UIRenderer(this));

        new UIManager(this);
        new EntityManager(this);
        new Overlay();
        Overlay::get()->setParent(this);

        if (DebugEnvironment::enabled() && DebugEnvironment::settings()["general"]["debugHud"]) {
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

    if (DebugEnvironment::enabled()) {
        DebugEnvironment::setDebugScreen();
    } else {
        Window::get()->setScreen(std::make_shared<MenuScreen>());
    }

    Window::get()->onResize(Window::get()->width(), Window::get()->height());
    Window::get()->show();

    s_running = true;
}

void Game::run() {
    Uint64 frequency = SDL_GetPerformanceFrequency();
    Uint64 currentTime = SDL_GetPerformanceCounter();

    while (s_running) {
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
    s_running = false;
}

std::string Game::currentDirectory() {
    return std::filesystem::current_path().string();
}

bool Game::isRunning() {
    return s_running;
}

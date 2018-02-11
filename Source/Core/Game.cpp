#include "Game.h"
#include "Utils.h"
#include "Defines.h"
#include "Event/Event.h"
#include "Event/Input.h"
#include "Resource/ResourceManager.h"
#include "Debug/Logger.h"
#include "Debug/DebugEnvironment.h"
#include "UI/Overlay.h"
#include "UI/UIManager.h"
#include "ECS/EntityManager.h"
#include "Core/Settings.h"
#include "Graphics/Render/RenderManager.h"
#include "Window.h"
#include "Screen/MenuScreen.h"
#include "World/World.h"
#include "SDLWrapper.h"
#include <string>
#include <SDL_timer.h>
#include <algorithm>
#include <memory>
#include <experimental/filesystem>

#if defined(OS_LINUX)
    #include <X11/Xlib-xcb.h>
#endif

namespace Origin {

bool Game::running = false;

Settings* Game::settings;
Logger* Game::logger;
DebugEnvironment* Game::debugEnvironment;
Event* Game::event;
Window* Game::window;
RenderManager* Game::renderManager;
UIManager* Game::uiManager;
EntityManager* Game::entityManager;
ResourceManager* Game::resourceManager;
Overlay* Game::overlay;
Input* Game::input;
World* Game::world;

Game::Game(int argc, char* argv[], Object* parent) : Object(parent) {
    for (int i = 0; i < argc; i++) {
        argvs.push_back(argv[i]);
    }

    init();
}

Game::~Game() {
    SDL::shutdown();
    resourceManager->cleanup();
}

void Game::init() {
    try {
        SDL::init();
        settings = new Settings(this);
        logger = new Logger(this);
        debugEnvironment = new DebugEnvironment(this);
        event = new Event(this);
        window = new Window(this);
        resourceManager = new ResourceManager(this);

        SDL_SysWMinfo wminfo = SDL::getSysWMinfo(window->getHandle());

#if defined(OS_WIN)
        renderManager = new RenderManager(GetModuleHandle(nullptr), (void*)wminfo.info.win.window, this);
#elif defined(OS_LINUX)
        renderManager = new RenderManager((void*)XGetXCBConnection(wminfo.info.x11.display), (void*)&wminfo.info.x11.window, this);
#endif

        if (debugEnvironment->getEnable()) {
            if (debugEnvironment->getSettings()["vulkan"]["layers"]["use"]) {
                renderManager->setEnabledLayers(debugEnvironment->getSettings()["vulkan"]["layers"]["list"]);
            }

            if (debugEnvironment->getSettings()["vulkan"]["extensions"]["use"]) {
                renderManager->setEnabledExtensions(debugEnvironment->getSettings()["vulkan"]["extensions"]["list"]);
            }

            renderManager->setDeviceIndex(debugEnvironment->getVulkanDevice());
        }
        renderManager->create();

        uiManager = new UIManager(this);
        entityManager = new EntityManager(this);
        overlay = new Overlay();
        overlay->setParent(this);
        input = new Input(this);
        world = new World(this);
    } catch (const std::exception& ex) {
        if (SDL::isInited()) {
            SDL::showErrorMessageBox(ex.what());
        } else {
            PRINT(ex.what());
        }
    }

    if (debugEnvironment->getEnable()) {
        debugEnvironment->setDebugScreen();
    } else {
        window->setScreen(std::make_shared<MenuScreen>());
    }

    window->onResize(window->getWidth(), window->getHeight());
    window->show();

    running = true;
}

void Game::run() {
    Uint64 frequency = SDL_GetPerformanceFrequency();
    Uint64 currentTime = SDL_GetPerformanceCounter();

    while (running) {
        event->handleEvents();
        window->invokeDeffered();
        overlay->invokeDeffered();

        Uint64 newTime = SDL_GetPerformanceCounter();
        double frameTime = double(newTime - currentTime) / frequency;
        currentTime = newTime;

        window->update(frameTime);
        window->render();
//        PRINT(frameTime << " " << 1 / frameTime)
    }
}

void Game::quit() {
    running = false;
}

std::string Game::getCurrentDirectory() {
    return std::experimental::filesystem::current_path().string();
}

Window* Game::getWindow() {
    return window;
}

UIManager* Game::getUIManager() {
    return uiManager;
}

EntityManager* Game::getEntityManager() {
    return entityManager;
}

Settings* Game::getSettings() {
    return settings;
}

Logger* Game::getLogger() {
    return logger;
}

DebugEnvironment* Game::getDebugEnvironment() {
    return debugEnvironment;
}

Event* Game::getEvent() {
    return event;
}

ResourceManager* Game::getResourceManager() {
    return resourceManager;
}

Input* Game::getInput() {
    return input;
}

World*Game::getWorld() {
    return world;
}

Overlay* Game::getOverlay() {
    return overlay;
}

RenderManager* Game::getRenderManager() {
    return renderManager;
}

bool Game::isRunning() {
    return running;
}

} // Origin

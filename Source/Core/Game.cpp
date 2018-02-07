#include "Game.h"
#include "Utils.h"
#include "Defines.h"
#include "Event/Event.h"
#include "Event/Input.h"
#include "Resource/ResourceManager.h"
#include "Debug/Logger.h"
#include "Debug/DebugEnvironment.h"
#include "Debug/DebugHUD.h"
#include "UI/UIManager.h"
#include "UI/UIRenderer.h"
#include "ECS/EntityManager.h"
#include "Core/Settings.h"
#include "Graphics/Render/RenderEngine.h"
#include "Window.h"
#include "Screen/MenuScreen.h"
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

namespace {
    std::vector<std::string> argvs;
    bool running = false;

    Logger* logger;
    Settings* settings;
    Window* window;
    RenderEngine* renderEngine;
    UIManager* uiManager;
    UIRenderer* uiRenderer;
    EntityManager* entityManager;
}

namespace Game {

void init(int argc, char* argv[]) {
    for (int i = 0; i < argc; i++) {
        argvs.push_back(argv[i]);
    }

    try {
        SDL::init();
        settings = new Settings;
        logger = new Logger;
        new DebugEnvironment;
        new Event;
        window = new Window;

        SDL_SysWMinfo wminfo = SDL::getSysWMinfo(window->getHandle());

#if defined(OS_WIN)
        renderEngine = new RenderEngine(GetModuleHandle(nullptr), (void*)wminfo.info.win.window);
#elif defined(OS_LINUX)
        renderEngine = new RenderEngine((void*)XGetXCBConnection(wminfo.info.x11.display), (void*)&wminfo.info.x11.window);
#endif

        if (DebugEnvironment::get()->getEnable()) {
            if (DebugEnvironment::get()->getSettings()["vulkan"]["layers"]["use"]) {
                renderEngine->setEnabledLayers(DebugEnvironment::get()->getSettings()["vulkan"]["layers"]["list"]);
            }

            if (DebugEnvironment::get()->getSettings()["vulkan"]["extensions"]["use"]) {
                renderEngine->setEnabledExtensions(DebugEnvironment::get()->getSettings()["vulkan"]["extensions"]["list"]);
            }

            renderEngine->setDeviceIndex(DebugEnvironment::get()->getVulkanDevice());
        }
        renderEngine->create();

        new ResourceManager;

        uiManager = new UIManager;
        uiRenderer = new UIRenderer;
        entityManager = new EntityManager;
        new DebugHUD;
        new Input;
    } catch (const std::exception& ex) {
        if (SDL::isInited()) {
            SDL::showErrorMessageBox(ex.what());
        } else {
            PRINT(ex.what());
        }
    }

    if (DebugEnvironment::get()->getEnable()) {
        DebugEnvironment::get()->setDebugScreen();
    } else {
        window->setScreen(std::make_shared<MenuScreen>());
    }

    window->show();

    running = true;
}

void shutdown() {
    Input::release();
    DebugHUD::release();
    ResourceManager::release();
    delete entityManager;
    delete uiRenderer;
    delete uiManager;
    delete window;
    delete renderEngine;
    SDL::shutdown();
    Event::release();
    DebugEnvironment::release();
    delete settings;
    delete logger;
}

void run() {
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

void quit() {
    running = false;
}

std::string getCurrentDirectory() {
    return std::experimental::filesystem::current_path().string();
}

Window* getWindow() {
    return window;
}

UIManager* getUIManager() {
    return uiManager;
}

UIRenderer* getUIRenderer() {
    return uiRenderer;
}

EntityManager* getEntityManager() {
    return entityManager;
}

Settings* getSettings() {
    return settings;
}

Logger* getLogger() {
    return logger;
}

} // Game

} // Origin

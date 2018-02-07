#include "Game.h"
#include "Utils.h"
#include "Defines.h"
#include "Context.h"
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
    std::unique_ptr<Window> window;
    std::unique_ptr<RenderEngine> renderEngine;
}

namespace Game {

std::string getCurrentDirectory() {
    return std::experimental::filesystem::current_path().string();
}

void init(int argc, char* argv[]) {
    for (int i = 0; i < argc; i++) {
        argvs.push_back(argv[i]);
    }

    try {
        // Order is important
        new Settings;
        new Logger;
        new DebugEnvironment;
        new Event;
        SDL::init();
        window = std::make_unique<Window>();

        SDL_SysWMinfo wminfo = SDL::getSysWMinfo(window->getHandle());

#if defined(OS_WIN)
        renderEngine = std::make_unique<RenderEngine>(GetModuleHandle(nullptr), (void*)wminfo.info.win.window);
#elif defined(OS_LINUX)
        renderEngine = std::make_unique<RenderEngine>((void*)XGetXCBConnection(wminfo.info.x11.display), (void*)&wminfo.info.x11.window);
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
        new Context;
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
    Context::release();
    ResourceManager::release();
    window.reset();
    renderEngine.reset();
    SDL::shutdown();
    Event::release();
    DebugEnvironment::release();
    Logger::release();
    Settings::release();
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

std::vector<std::string>& getArgv() {
    return argvs;
}

bool isRunning() {
    return running;
}

Window* getWindow() {
    return window.get();
}

} // Game

} // Origin

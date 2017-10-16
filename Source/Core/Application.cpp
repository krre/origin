#include "Application.h"
#include "Core/Context.h"
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
#include "Graphics/Vulkan/VulkanCore.h"
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
    Game::get()->release();
    Input::get()->release();
    DebugHUD::get()->release();
    DebugEnvironment::get()->release();
    ResourceManager::get()->release();
    RendererSet::get()->release();
    window.reset();
    RenderManager::get()->release();
    VulkanCore::get()->release();
    SDLWrapper::get()->release();
    Context::get()->release();
    Event::get()->release();
    Logger::get()->release();
    Settings::get()->release();
}

std::string Application::getCurrentPath() {
    return std::experimental::filesystem::current_path().string();
}

void Application::init() {
    try {
        // Order is important
        new Settings;
        new Logger;
        new Event;
        new Context;

        new SDLWrapper;
        SDLWrapper::get()->init();

        new VulkanCore;
        new RenderManager;

        window = std::make_unique<RenderWindow>();
        window->setColor(Color::GREEN); // TODO: Temporary for debug

        new RendererSet;
        new ResourceManager;
        new DebugEnvironment;
        new DebugHUD;
        new Input;
        new Game;
    } catch (const std::exception& ex) {
        if (SDLWrapper::exists() && SDLWrapper::get()->getIsInited()) {
            SDLWrapper::get()->showErrorMessageBox(ex.what());
        } else {
            ERROR(ex.what());
        }
    }

    Event::get()->quit.connect<Application, &Application::quit>(this);
    Event::get()->windowResize.emit(window->getWidth(), window->getHeight());

    window->show();

    isRunning = true;
}

void Application::run() {
    Uint64 frequency = SDL_GetPerformanceFrequency();
    Uint64 currentTime = SDL_GetPerformanceCounter();

    while (isRunning) {
        Event::get()->handleEvents();

        Uint64 newTime = SDL_GetPerformanceCounter();
        double frameTime = double(newTime - currentTime) / frequency;
        currentTime = newTime;

        Game::get()->update(frameTime);
        Game::get()->render(frameTime);
    }
}

/*
int Application::run() {
    // Game loop is based on article http://gafferongames.com/game-physics/fix-your-timestep/
    const double dt = 0.01;
    Uint64 frequency = SDL_GetPerformanceFrequency();
    Uint64 currentTime = SDL_GetPerformanceCounter();
    double accumulator = 0.0;

    while (isRunning) {
        Event::get()->handleEvents();

        Uint64 newTime = SDL_GetPerformanceCounter();
        double frameTime = double(newTime - currentTime) / frequency;
        currentTime = newTime;
        accumulator += frameTime;

        while (accumulator >= dt) {
            EntityManager::get()->process(dt, EntityManager::UPDATE);
            accumulator -= dt;
        }

        EntityManager::get()->process(dt, EntityManager::RENDER);
        SDL_GL_SwapWindow(window);
    }
}
*/

void Application::quit() {
    isRunning = false;
}

#include "App.h"
#include "Window.h"
#include "Game.h"
#include "Utils.h"
#include "Event/Event.h"
#include "Event/Input.h"
#include "Resource/ResourceManager.h"
#include "Debug/Logger.h"
#include "Debug/DebugEnvironment.h"
#include "Debug/DebugHUD.h"
#include "Scene/SceneManager.h"
#include "Core/Settings.h"
#include "Graphics/Renderer.h"
#include "Graphics/Vulkan/Instance.h"
#include <string>
#include <SDL_timer.h>
#include <Origin.h>
#include <algorithm>
#include <experimental/filesystem>

const char* title = "Origin";

App::App(int argc, char* argv[]) {
    for (int i = 0; i < argc; i++) {
        this->argv.push_back(argv[i]);
    }
}

App::~App() {
    Game::get()->release();
    SceneManager::get()->release();
    Input::get()->release();
    DebugHUD::get()->release();
    DebugEnvironment::get()->release();
    ResourceManager::get()->release();
    Renderer::get()->release();
    Event::get()->release();
    Logger::get()->release();
    Settings::get()->release();
    SDL_DestroyWindow(window);
    SDL_Quit();
}

std::string App::getCurrentPath() {
    return std::experimental::filesystem::current_path().string();
}

void App::init() {
    new Settings("origin.ini");
    new Logger;
    new Event;

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL could not initialize! SDL_Error: %s", SDL_GetError());
        return;
    }

    SDL_DisplayMode mode;
    if (SDL_GetDesktopDisplayMode(0, &mode) != 0) {
        std::string errorMsg = std::string("SDL_GetDesktopDisplayMode failed\n") + SDL_GetError();
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title, errorMsg.c_str(), nullptr);
        return;
    }

    if (SDL_GetDisplayMode(0, 0, &mode) != 0) {
        std::string errorMsg = std::string("SDL_GetDisplayMode failed\n") + SDL_GetError();
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title, errorMsg.c_str(), nullptr);
        return;
    }

    int screenWidth = mode.w;
    int screenHeight = mode.h;

    // Check dual monitor, and if current screen width is larger then maximum monitor resolution,
    // then divide it on 2
    if (screenWidth > mode.w) {
        screenWidth /= 2;
    }

    std::string settingsX = Settings::get()->getValue("x");
    std::string settingsY = Settings::get()->getValue("y");
    std::string settingsWidth = Settings::get()->getValue("width");
    std::string settingsHeigth = Settings::get()->getValue("height");

    int x = settingsX.empty() ? (screenWidth - WINDOW_WIDTH) / 2 : std::stoi(settingsX);
    int y = settingsY.empty() ? (screenHeight - WINDOW_HEIGHT) / 2 : std::stoi(settingsY);
    width = settingsWidth.empty() ? WINDOW_WIDTH : std::stoi(settingsWidth);
    height = settingsHeigth.empty() ? WINDOW_HEIGHT : std::stoi(settingsHeigth);

    window = SDL_CreateWindow(title, x, y, width, height, SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE);

    if (window == nullptr) {
        std::string errorMsg = std::string("Window could not be created\n") + SDL_GetError();
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title, errorMsg.c_str(), nullptr);
        return;
    }

    new Renderer; // TODO: Catch exception on failure Vulkan initialization

    SDL_ShowWindow(window);

//    try {
//        win = std::unique_ptr<Window>(new Window);
//        win->show();
//    } catch (const std::exception& ex) {
//        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, win->getTitle().c_str(), ex.what(), nullptr);
//    }

    // Order is important
    new ResourceManager;
    new DebugEnvironment;
    new DebugHUD;
    new Input;
    new SceneManager;
    new Game;

    Event::get()->windowMove.connect<App, &App::windowMove>(this);
    Event::get()->windowResize.connect<App, &App::windowResize>(this);
    Event::get()->quit.connect<App, &App::quit>(this);
    Event::get()->windowResize.emit(width, height);

    isRunning = true;
}

int App::run() {
    Uint64 frequency = SDL_GetPerformanceFrequency();
    Uint64 currentTime = SDL_GetPerformanceCounter();

    while (isRunning) {
        Event::get()->handleEvents();

        Uint64 newTime = SDL_GetPerformanceCounter();
        double frameTime = double(newTime - currentTime) / frequency;
        currentTime = newTime;

        SceneManager::get()->update(frameTime);
        SceneManager::get()->draw(frameTime);
    }

    Vulkan::Instance::get()->getDefaultDevice()->waitIdle();
}

/*
int App::run() {
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

void App::windowResize(int width, int height) {
    this->width = width;
    this->height = height;
    Settings::get()->setValue("width", std::to_string(width));
    Settings::get()->setValue("height", std::to_string(height));

    if (isRunning) {
        Vulkan::Instance::get()->windowResize(width, height);
        SceneManager::get()->rebuild();
    }
}

void App::windowMove(int x, int y) {
    Settings::get()->setValue("x", std::to_string(x));
    Settings::get()->setValue("y", std::to_string(y));
}

void App::quit() {
    isRunning = false;
}

#include "App.h"
#include "Game.h"
#include "Utils.h"
#include "../Graphics/Vulkan/Manager.h"
#include "../Event/Event.h"
#include "../Event/Input.h"
#include "../Resource/ResourceManager.h"
#include "../Debug/Console.h"
#include "../Debug/Logger.h"
#include "../Debug/DebugHUD.h"
#include "../UI/Toast.h"
#include "../ECS/Engine.h"
#include "../GameState/GameStateManager.h"
#include <string>
#include <SDL_timer.h>
#include <Gagarin.h>
#include <algorithm>
#include <experimental/filesystem>

const char* title = "Gagarin";

App::App(int argc, char* argv[]) {
    for (int i = 0; i < argc; i++) {
        this->argv.push_back(argv[i]);
    }
}

App::~App() {
    clean();
}

std::string App::getCurrentPath() {
    return std::experimental::filesystem::current_path().string();
}

void App::init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        error("SDL could not initialize! SDL_Error: " << SDL_GetError());
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

    int x = (screenWidth - WIDTH) / 2;
    int y = (screenHeight - HEIGHT) / 2;

    window = SDL_CreateWindow(title, x, y, WIDTH, HEIGHT, SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE);

    if (window == nullptr) {
        std::string errorMsg = std::string("Window could not be created\n") + SDL_GetError();
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title, errorMsg.c_str(), nullptr);
        return;
    }

    new Vulkan::Manager;
    if (Vulkan::Manager::get()->createInstance() != VK_SUCCESS) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title, Vulkan::Manager::get()->getInstance()->getResultDescription().c_str(), nullptr);
        return;
    }

    SDL_ShowWindow(window);

    // Order is important
    new Logger;
    new Event;
    new ResourceManager;
    Vulkan::Manager::get()->init(); // After init resources with shaders
    new Console;
    new DebugHUD;
    new Toast;
    new Input;
    new Engine;
    new GameStateManager;
    new Game;

    Event::get()->windowResize.connect<App, &App::windowResize>(this);
    Event::get()->quit.connect<App, &App::quit>(this);
    Event::get()->windowResize.emit(width, height);

    isRunning = true;
}

void App::clean() {
    Vulkan::Manager::get()->release();
    SDL_DestroyWindow(window);
    SDL_Quit();
    Game::get()->release();
    GameStateManager::get()->release();
    Engine::get()->release();
    Input::get()->release();
    Event::get()->release();
    ResourceManager::get()->release();
    Console::get()->release();
    DebugHUD::get()->release();
    Toast::get()->release();
    Logger::get()->release();
}

int App::run() {
    Uint64 frequency = SDL_GetPerformanceFrequency();
    Uint64 currentTime = SDL_GetPerformanceCounter();

    while (isRunning) {
        Event::get()->handleEvents();

        Uint64 newTime = SDL_GetPerformanceCounter();
        double frameTime = double(newTime - currentTime) / frequency;
        currentTime = newTime;

        GameStateManager::get()->update(frameTime);
        GameStateManager::get()->draw(frameTime);
        Vulkan::Manager::get()->render();
    }

    Vulkan::Manager::get()->getDevice()->waitIdle();
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
            Engine::get()->process(dt, Engine::UPDATE);
            accumulator -= dt;
        }

        Engine::get()->process(dt, Engine::RENDER);
        SDL_GL_SwapWindow(window);
    }
}
*/

void App::windowResize(int width, int height) {
    this->width = width;
    this->height = height;
    viewport.setRectangle(0, 0, width, height);
}

void App::quit() {
    isRunning = false;
}

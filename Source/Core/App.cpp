#include "App.h"
#include "Game.h"
#include "../Event/Event.h"
#include "../Event/Input.h"
#include "../Resource/ResourceManager.h"
#include "../Debug/Console.h"
#include "../Debug/Logger.h"
#include "../Debug/DebugHUD.h"
#include "../UI/Toast.h"
#include "../ECS/Engine.h"
#include <string>
#include <SDL_timer.h>
#include <GL/glew.h>
#include <Gagarin.h>

std::string App::absoluteFilePath;
std::string App::absolutePath;

App::App(int argc, char* argv[]) {
    for (int i = 0; i < argc; i++) {
        this->argv.push_back(argv[i]);
    }
    absoluteFilePath = this->argv[0];
    absolutePath = absoluteFilePath.substr(0, absoluteFilePath.find_last_of(getPathSeparator()));

    init();
}

App::~App() {
    clean();
}

std::string App::getPathSeparator() {
#ifdef __WINDOWS__
    return "\\";
#else
    return "/";
#endif
}

void App::init() {
    print("Gagarin " << VERSION_STRING);
//    SDL_version compiled;
//    SDL_VERSION(&compiled);
//    std::string sdlVersion = "SDL " + std::to_string(compiled.major) + "." + std::to_string(compiled.minor) + "." + std::to_string(compiled.patch);
//    print(sdlVersion);

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        error("SDL could not initialize! SDL_Error: " << SDL_GetError());
    } else {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        int screenWidth;
        int screenHeight;

        SDL_DisplayMode mode;
        if (SDL_GetDesktopDisplayMode(0, &mode) != 0) {
            SDL_Log("SDL_GetDesktopDisplayMode failed: %s", SDL_GetError());
        } else {
            screenWidth = mode.w;
            screenHeight = mode.h;
            // Check dual monitor, and if current screen width is larger then maximum monitor resolution,
            // then divide it on 2
            if (SDL_GetDisplayMode(0, 0, &mode) != 0) {
                SDL_Log("SDL_GetDisplayMode failed: %s", SDL_GetError());
            } else {
                if (screenWidth > mode.w) {
                    screenWidth /= 2;
                }
            }
        }

        int x = (screenWidth - WINDOW_WIDTH) / 2;
        int y = (screenHeight - WINDOW_HEIGHT) / 2;

        window = SDL_CreateWindow("Gagarin",
            x,
            y,
            WINDOW_WIDTH,
            WINDOW_HEIGHT,
            SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
        if (window == nullptr) {
            error("Window could not be created! SDL_Error: " << SDL_GetError());
        } else {
            context = SDL_GL_CreateContext(window);
            if (context == nullptr) {
                error("OpenGL context could not be created! SDL_Error: " << SDL_GetError());
            } else {
                SDL_GL_MakeCurrent(window, context);

                SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
                SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
                SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
                SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

                glewExperimental = GL_TRUE;
                glewInit();
                isRunning = true;
            }
        }

        initSingletons();
    }
}

void App::clean() {
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    Engine::getInstance()->release();
    Event::getInstance()->release();
    Input::getInstance()->release();
    ResourceManager::getInstance()->release();
    Console::getInstance()->release();
    DebugHUD::getInstance()->release();
    Toast::getInstance()->release();
    Logger::getInstance()->release();
    delete viewport;
}

int App::run() {
    Uint64 frequency = SDL_GetPerformanceFrequency();
    Uint64 currentTime = SDL_GetPerformanceCounter();

    while (isRunning) {
        Event::getInstance()->handleEvents();

        Uint64 newTime = SDL_GetPerformanceCounter();
        double frameTime = double(newTime - currentTime) / frequency;
        currentTime = newTime;
        Engine::getInstance()->process(frameTime);

        SDL_GL_SwapWindow(window);
    }
}

/*
int App::run() {
    // Game loop is based on article http://gafferongames.com/game-physics/fix-your-timestep/
    const double dt = 0.01;
    Uint64 frequency = SDL_GetPerformanceFrequency();
    Uint64 currentTime = SDL_GetPerformanceCounter();
    double accumulator = 0.0;

    while (isRunning) {
        Event::getInstance()->handleEvents();

        Uint64 newTime = SDL_GetPerformanceCounter();
        double frameTime = double(newTime - currentTime) / frequency;
        currentTime = newTime;
        accumulator += frameTime;

        while (accumulator >= dt) {
            Engine::getInstance()->process(dt, Engine::UPDATE);
            accumulator -= dt;
        }

        Engine::getInstance()->process(dt, Engine::RENDER);
        SDL_GL_SwapWindow(window);
    }
}
*/

void App::windowResize(int width, int height) {
    this->width = width;
    this->height = height;
    viewport->setRectangle(0, 0, width, height);
}

void App::initSingletons() {
    new Logger();
    new Event();
    new ResourceManager();
    ResourceManager::getInstance()->loadAll();
    new Console();
    new DebugHUD();
    new Toast();
    new Input();
    new Engine();

    viewport = new Viewport();

    new Game();
    Game::getInstance()->create();

    Event::getInstance()->windowResize.connect<App, &App::windowResize>(this);
    Event::getInstance()->quit.connect<App, &App::quit>(this);
    Event::getInstance()->windowResize.emit(width, height);
}

void App::quit() {
    isRunning = false;
}

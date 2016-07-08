#include "App.h"
#include "Game.h"
#include "../Event/Event.h"
#include "../Event/Input.h"
#include "../Resource/Resource.h"
#include "../Debug/Console.h"
#include "../Debug/Logger.h"
#include <string>
#include <SDL_timer.h>
#include <GL/glew.h>

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 480;

string App::absoluteFilePath;
string App::absolutePath;

App::App(int argc, char* argv[]) {
    for (int i = 0; i < argc; i++) {
        this->argv.push_back(argv[i]);
    }
    absoluteFilePath = this->argv[0];
    absolutePath = absoluteFilePath.substr(0, absoluteFilePath.find_last_of(getPathSeparator()));
}

App::~App() {
    Event::getInstance()->release();
    Input::getInstance()->release();
    Resource::getInstance()->release();
    Console::getInstance()->release();
    Logger::getInstance()->release();
    delete viewport;
}

string App::getPathSeparator() {
#ifdef __WINDOWS__
    return "\\";
#else
    return "/";
#endif
}

void App::init() {
    SDL_version compiled;
    SDL_VERSION(&compiled);
    string sdlVersion = "SDL " + to_string(compiled.major) + "." + to_string(compiled.minor) + "." + to_string(compiled.patch);
    cout << sdlVersion << endl;

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
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
            cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
        } else {
            context = SDL_GL_CreateContext(window);
            if (context == nullptr) {
                cout << "OpenGL context could not be created! SDL_Error: " << SDL_GetError() << endl;
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

        new Event();
        new Input();
        new Resource();
        new Console();
        new Logger();

        viewport = new Viewport();

        Event::getInstance()->windowResize.connectMember(&App::windowResize, this, std::placeholders::_1, std::placeholders::_2);
        Event::getInstance()->quit.connectMember(&App::quit, this);

        new Game();
        Game::getInstance()->create();
    }
}

void App::clean() {
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

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
            Event::getInstance()->update.emit(dt);
            accumulator -= dt;
        }

        Event::getInstance()->render.emit();
        SDL_GL_SwapWindow(window);
    }
}

void App::windowResize(int width, int height) {
    this->width = width;
    this->height = height;
    glViewport(0, 0, width, height);
}

void App::quit() {
    isRunning = false;
}

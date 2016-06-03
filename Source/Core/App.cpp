#include "App.h"
#include <string>
#include <SDL_timer.h>

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 480;

App::App() {

}

App::~App() {
    delete game;
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
                isRunning = true;
            }
        }

        game = new Game();
        game->create();
        game->addView(shared_ptr<PlayerView>(new PlayerView));
    }
}

void App::handleEvents() {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_WINDOWEVENT:
            switch (event.window.event) {
            case SDL_WINDOWEVENT_RESIZED:
                windowResize(event.window.data1, event.window.data2);
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
    }
}

void App::clean() {
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
        handleEvents();

        Uint64 newTime = SDL_GetPerformanceCounter();
        double frameTime = double(newTime - currentTime) / frequency;
        currentTime = newTime;
        accumulator += frameTime;

        while (accumulator >= dt) {
            update.emit(dt);
            accumulator -= dt;
        }

        render.emit();
        SDL_GL_SwapWindow(window);
    }
}

void App::windowResize(int width, int height) {
    print(width << " " << height)
}

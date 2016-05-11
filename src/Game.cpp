#include "Game.h"
#include <iostream>
#include <string>
#include "3rdparty/SDL/include/SDL_version.h"
#include "3rdparty/SDL/include/SDL_events.h"

using namespace std;

// Default screen dimension
constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 480;

void Game::init() {
    SDL_version compiled;
    SDL_VERSION(&compiled);
    string sdlVersion = "SDL " + to_string(compiled.major) + "." + to_string(compiled.minor) + "." + to_string(compiled.patch);
    cout << sdlVersion << endl;

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
    } else {
        window = SDL_CreateWindow("Gagarin",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
        if (window == nullptr) {
            cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
        } else {
            surface = SDL_GetWindowSurface(window);
            running = true;
        }
    }
}

void Game::render() {
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 40, 40, 40));
    SDL_UpdateWindowSurface(window);
}

void Game::update() {

}

void Game::handleEvents() {
    SDL_Event event;
    if(SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            running = false;
            break;
        default:
            break;
        }
    }
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int Game::run() {
    while (running) {
        handleEvents();
        update();
        render();
    }
}

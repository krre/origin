#include "Game.h"
#include <iostream>
#include <string>
#include <SDL_opengl.h>

using namespace std;

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
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        window = SDL_CreateWindow("Gagarin",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
        if (window == nullptr) {
            cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
        } else {
            context = SDL_GL_CreateContext(window);
            if (context == nullptr) {
                cout << "OpenGL context could not be created! SDL_Error: " << SDL_GetError() << endl;
            } else {
                glClearColor(0.2, 0.2, 0.2, 1.0);
                running = true;
            }
        }
    }
}

void Game::render() {
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(window);
}

void Game::update() {

}

void Game::handleEvents() {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            running = false;
            break;
        case SDL_WINDOWEVENT:
            switch (event.window.event) {
            case SDL_WINDOWEVENT_RESIZED:
                onWindowResize(event.window.data1, event.window.data2);
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

void Game::onWindowResize(int width, int height) {
    cout << width << " " << height << endl;
}

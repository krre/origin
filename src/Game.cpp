#include "Game.h"
#include <stdlib.h>
#include <iostream>
#include "SDL/include/SDL_version.h"
#include "SDL/include/SDL.h"

// Default screen dimension
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 480;

Game::Game() {

}

int Game::run() {
    SDL_version compiled;
    SDL_VERSION(&compiled);
    printf("SDL %d.%d.%d\n", compiled.major, compiled.minor, compiled.patch);

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    } else {
        SDL_Window* window = SDL_CreateWindow("Gagarin", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == nullptr) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            return EXIT_FAILURE;
        } else {
            SDL_Surface* screenSurface = SDL_GetWindowSurface(window);
            SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 40, 40, 40));
            SDL_UpdateWindowSurface(window);
            SDL_Delay(2000);
            SDL_DestroyWindow(window);
            SDL_Quit();

            return EXIT_SUCCESS;
        }
    }
}

#include "Game.h"
#include <stdlib.h>
#include <iostream>
#include "SDL/include/SDL_version.h"
#include "SDL/include/SDL.h"

// Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 480;

Game::Game() {

}

int Game::run() {
    SDL_version compiled;
    SDL_VERSION(&compiled);
    printf("SDL %d.%d.%d\n", compiled.major, compiled.minor, compiled.patch);

    // The window we'll be rendering to
    SDL_Window* window = nullptr;

    // The surface contained by the window
    SDL_Surface* screenSurface = nullptr;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    } else {
        // Create window
        window = SDL_CreateWindow("Gagarin", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == nullptr) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        } else {
            // Get window surface
            screenSurface = SDL_GetWindowSurface(window);

            // Fill the surface white
            SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 40, 40, 40));

            // Update the surface
            SDL_UpdateWindowSurface(window);

            // Wait two seconds
            SDL_Delay(2000);
        }
    }

    // Destroy window
    SDL_DestroyWindow(window);

    SDL_Quit();

    return EXIT_SUCCESS;
}

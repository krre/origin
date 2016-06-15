#pragma once
#include <SDL.h>
#include <vector>
#include "../Event/Event.h"
#include "../Graphics/Renderer.h"
#include "Game.h"
#include "Object.h"
#include "../Scene/Viewport.h"

class App : public Object {

public:
    App(int argc, char* argv[]);
    ~App();
    // Full path to application
    string getAbsoluteFilePath() { return absoluteFilePath; }
    // Path to application directory
    string getAbsolutePath() { return absolutePath; }
    string getPathSeparator();
    void init();
    void clean();
    int run();
    void quit();
    Viewport* getViewport() { return &viewport; }
    SDL_Window* getWindow() const { return window; }

private:
    vector<string> argv;
    string absoluteFilePath;
    string absolutePath;

    Game* game;
    Renderer renderer;
    Viewport viewport;

    bool isRunning = false;
    SDL_Window* window = nullptr;
    SDL_GLContext context;

    void windowResize(int width, int height);
};

#pragma once
#include <SDL.h>
#include <vector>
#include "../Event/Event.h"
#include "../Graphics/Renderer.h"
#include "Singleton.h"
#include "../Scene/Viewport.h"

class App : public Singleton<App> {

public:
    App(int argc, char* argv[]);
    ~App();
    // Full path to application
    static string getAbsoluteFilePath() { return absoluteFilePath; }
    // Path to application directory
    static string getAbsolutePath() { return absolutePath; }
    static string getPathSeparator();
    void init();
    void clean();
    int run();
    void quit();
    Viewport* getViewport() { return viewport; }
    SDL_Window* getWindow() const { return window; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }

private:
    vector<string> argv;
    static string absoluteFilePath;
    static string absolutePath;

    Renderer renderer;
    Viewport* viewport;

    bool isRunning = false;
    SDL_Window* window = nullptr;
    SDL_GLContext context;

    int width;
    int height;

    void windowResize(int width, int height);
    void initSingletons();
};

#pragma once
#include <SDL.h>
#include <vector>
#include "../Event/Event.h"
#include "Singleton.h"
#include "../UI/Viewport.h"

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 480;

class App : public Singleton<App> {

public:
    App(int argc, char* argv[]);
    ~App();
    // Full path to application
    static std::string getAbsoluteFilePath() { return absoluteFilePath; }
    // Path to application directory
    static std::string getAbsolutePath() { return absolutePath; }
    int run();
    void quit();
    Viewport* getViewport() { return &viewport; }
    SDL_Window* getWindow() const { return window; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }

private:
    std::vector<std::string> argv;
    static std::string absoluteFilePath;
    static std::string absolutePath;

    Viewport viewport;

    bool isRunning = false;
    SDL_Window* window = nullptr;
    SDL_GLContext context;

    int width = WINDOW_WIDTH;
    int height = WINDOW_HEIGHT;

    void init();
    void clean();
    void windowResize(int width, int height);
    void initSingletons();
};

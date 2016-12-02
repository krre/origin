#pragma once
#include "../Event/Event.h"
#include "Singleton.h"
#include "../UI/Viewport.h"
#include <SDL_video.h>
#include <vector>

constexpr int WIDTH = 800;
constexpr int HEIGHT = 480;

class App : public Singleton<App> {

public:
    App(int argc, char* argv[]);
    ~App();
    // Path to application directory
    static std::string getCurrentPath();

    void init();
    int run();
    void quit();

    Viewport* getViewport() { return &viewport; }
    SDL_Window* getWindow() const { return window; }

    int getWidth() const { return width; }
    int getHeight() const { return height; }

private:
    std::vector<std::string> argv;
    Viewport viewport;
    bool isRunning = false;
    SDL_Window* window = nullptr;
    SDL_GLContext context;

    int width = WIDTH;
    int height = HEIGHT;

    void clean();
    void windowResize(int width, int height);
};

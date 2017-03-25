#pragma once
#include "Singleton.h"
#include <SDL_video.h>
#include <vector>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 480;

class App : public Singleton<App> {

public:
    App(int argc, char* argv[]);
    ~App();
    // Path to application directory
    static std::string getCurrentPath();

    void init();
    int run();
    void quit();

    SDL_Window* getWindow() const { return window; }

    int getWidth() const { return width; }
    int getHeight() const { return height; }

private:
    std::vector<std::string> argv;
    bool isRunning = false;
    SDL_Window* window = nullptr;
    SDL_GLContext context;

    int width = WINDOW_WIDTH;
    int height = WINDOW_HEIGHT;

    void clean();
    void windowResize(int width, int height);
    void windowMove(int x, int y);
};

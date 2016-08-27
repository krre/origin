#pragma once
#include <SDL.h>
#include <vector>
#include "../Event/Event.h"
#include "../Graphics/Renderer.h"
#include "Singleton.h"
#include "../UI/Viewport.h"

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 480;

enum class RendererType {
    CPU,
    GPU
};

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
    RendererType getRendererType() { return rendererType; }
    void setRendererType(RendererType rendererType) { this->rendererType = rendererType; }

private:
    std::vector<std::string> argv;
    static std::string absoluteFilePath;
    static std::string absolutePath;

    Renderer renderer;
    Viewport viewport;

    bool isRunning = false;
    SDL_Window* window = nullptr;
    SDL_GLContext context;
    RendererType rendererType = RendererType::GPU;

    int width = WINDOW_WIDTH;
    int height = WINDOW_HEIGHT;

    void init();
    void clean();
    void windowResize(int width, int height);
    void initSingletons();
};

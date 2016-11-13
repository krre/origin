#pragma once
#include "../Event/Event.h"
#include "Singleton.h"
#include "../UI/Viewport.h"
#include "../Graphics/Vulkan/Instance.h"
#include "../Graphics/Vulkan/PhysicalDevice.h"
#include <SDL.h>
#include <vector>

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 480;

class App : public Singleton<App> {

public:
    enum GraphicsBackend {
        VULKAN,
        OPENGL
    };

    App(int argc, char* argv[]);
    ~App();
    // Path to application directory
    static std::string getCurrentPath();

    void init();
    int run();
    void quit();

    void setBackend(GraphicsBackend graphicsBackend);
    GraphicsBackend getBackend() const { return graphicsBackend; }

    Viewport* getViewport() { return &viewport; }
    SDL_Window* getWindow() const { return window; }

    int getWidth() const { return width; }
    int getHeight() const { return height; }

private:
    std::vector<std::string> argv;
    GraphicsBackend graphicsBackend = VULKAN;
    Vulkan::Instance vulkanInstance;
    Viewport viewport;
    std::unique_ptr<Vulkan::PhysicalDevice> vulkanPhysicalDevice;

    bool isRunning = false;
    SDL_Window* window = nullptr;
    SDL_GLContext context;

    int width = WINDOW_WIDTH;
    int height = WINDOW_HEIGHT;

    void clean();
    void windowResize(int width, int height);
    void initSingletons();
};

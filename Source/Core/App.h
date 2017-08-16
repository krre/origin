#pragma once
#include "Singleton.h"
#include <vector>

class GameWindow;

namespace Vulkan {
    class Instance;
}

class App : public Singleton<App> {

public:
    App(int argc, char* argv[]);
    ~App();
    // Path to application directory
    static std::string getCurrentPath();

    void init();
    void run();
    void quit();

    GameWindow* getWindow() const { return window.get(); }
    bool getIsRunning() const { return isRunning; }

private:
    std::vector<std::string> argv;
    bool isRunning = false;
    std::unique_ptr<GameWindow> window;
    std::unique_ptr<Vulkan::Instance> vulkan;
};

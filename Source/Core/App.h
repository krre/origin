#pragma once
#include "Singleton.h"
#include <vector>

class RenderWindow;

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

    RenderWindow* getWindow() const { return window; }
    bool getIsRunning() const { return isRunning; }
    const std::vector<std::string>& getArgv() const { return argv; }

private:
    std::vector<std::string> argv;
    bool isRunning = false;
    RenderWindow* window;
    std::unique_ptr<Vulkan::Instance> vulkan;
};

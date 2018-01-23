#pragma once
#include "Singleton.h"
#include <vector>

namespace Origin {

class Window;
class RenderEngine;

class Application : public Singleton<Application> {

public:
    Application(int argc, char* argv[]);
    ~Application();
    // Path to Application directory
    static std::string getCurrentDirectory();

    void run();
    void quit();

    Window* getWindow() const { return window.get(); }
    bool isRunning() const { return running; }
    const std::vector<std::string>& getArgv() const { return argv; }

private:
    void init();

    std::vector<std::string> argv;
    bool running = false;
    std::unique_ptr<Window> window;
    std::unique_ptr<RenderEngine> renderEngine;
};

} // Origin

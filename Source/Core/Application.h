#pragma once
#include "Singleton.h"
#include <vector>

namespace Origin {

class RenderWindow;

class Application : public Singleton<Application> {

public:
    Application(int argc, char* argv[]);
    ~Application();
    // Path to Application directory
    static std::string getCurrentPath();

    void run();
    void quit();

    RenderWindow* getWindow() const { return renderWindow.get(); }
    bool isRunning() const { return running; }
    const std::vector<std::string>& getArgv() const { return argv; }

private:
    void init();

    std::vector<std::string> argv;
    bool running = false;
    std::shared_ptr<RenderWindow> renderWindow;
};

} // Origin

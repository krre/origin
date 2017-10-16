#pragma once
#include "Singleton.h"
#include <vector>

class RenderWindow;

class Application : public Singleton<Application> {

public:
    Application(int argc, char* argv[]);
    ~Application();
    // Path to Application directory
    static std::string getCurrentPath();

    void run();
    void quit();

    RenderWindow* getWindow() const { return window.get(); }
    bool getIsRunning() const { return isRunning; }
    const std::vector<std::string>& getArgv() const { return argv; }

private:
    void init();

    std::vector<std::string> argv;
    bool isRunning = false;
    std::unique_ptr<RenderWindow> window;
};

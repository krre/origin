#pragma once
#include "Singleton.h"
#include <vector>

class RenderWindow;

class App : public Singleton<App> {

public:
    App(int argc, char* argv[]);
    ~App();
    // Path to application directory
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
    std::shared_ptr<RenderWindow> window;
};

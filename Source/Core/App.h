#pragma once
#include "Singleton.h"
#include <vector>

class GameWindow;

class App : public Singleton<App> {

public:
    App(int argc, char* argv[]);
    ~App();
    // Path to application directory
    static std::string getCurrentPath();

    void init();
    int run();
    void quit();

    GameWindow* getWindow() const { return window.get(); }
    bool getIsRunning() const { return isRunning; }

private:
    std::vector<std::string> argv;
    bool isRunning = false;
    std::unique_ptr<GameWindow> window;

    void clean();
};

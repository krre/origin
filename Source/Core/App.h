#pragma once
#include "Singleton.h"
#include <vector>

class Window;

class App : public Singleton<App> {

public:
    App(int argc, char* argv[]);
    ~App();
    // Path to application directory
    static std::string getCurrentPath();

    void init();
    int run();
    void quit();

    Window* getWindow() const { return window.get(); }

    bool getIsRunning() const { return isRunning; }

private:
    std::vector<std::string> argv;
    bool isRunning = false;
    std::unique_ptr<Window> window;

    void clean();
    void windowResize(int width, int height);
};

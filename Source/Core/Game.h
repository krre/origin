#pragma once
#include <string>
#include <vector>

namespace Origin {

class Window;
class RenderEngine;

namespace Game {

    void init(int argc, char* argv[]);
    void shutdown();

    // Path to Game directory
    std::string getCurrentDirectory();

    void run();
    void quit();

    Window* getWindow();
    bool isRunning();
    std::vector<std::string>& getArgv();

} // Game

} // Origin

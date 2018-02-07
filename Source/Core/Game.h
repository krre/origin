#pragma once
#include <string>
#include <vector>

namespace Origin {

class Window;
class RenderEngine;
class UIManager;
class UIRenderer;
class EntityManager;

namespace Game {

    void init(int argc, char* argv[]);
    void shutdown();

    // Path to Game directory
    std::string getCurrentDirectory();

    void run();
    void quit();

    Window* getWindow();
    UIManager* getUIManager();
    UIRenderer* getUIRenderer();
    EntityManager* getEntityManager();

    bool isRunning();
    std::vector<std::string>& getArgv();

} // Game

} // Origin

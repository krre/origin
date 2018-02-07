#pragma once
#include <string>
#include <vector>

namespace Origin {

class Logger;
class Window;
class Settings;
class DebugEnvironment;
class Event;
class RenderEngine;
class UIManager;
class EntityManager;
class ResourceManager;
class Overlay;
class Input;

namespace Game {

    void init(int argc, char* argv[]);
    void shutdown();

    // Path to Game directory
    std::string getCurrentDirectory();

    void run();
    void quit();

    Logger* getLogger();
    Window* getWindow();
    Settings* getSettings();
    RenderEngine* getRenderEngine();
    UIManager* getUIManager();
    EntityManager* getEntityManager();
    DebugEnvironment* getDebugEnvironment();
    Event* getEvent();
    ResourceManager* getResourceManager();
    Overlay* getOverlay();
    Input* getInput();

    bool isRunning();
    std::vector<std::string>& getArgv();

} // Game

} // Origin

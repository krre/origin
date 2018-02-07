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
class UIRenderer;
class EntityManager;
class ResourceManager;
class DebugHUD;

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
    UIManager* getUIManager();
    UIRenderer* getUIRenderer();
    EntityManager* getEntityManager();
    DebugEnvironment* getDebugEnvironment();
    Event* getEvent();
    ResourceManager* getResourceManager();
    DebugHUD* getDebugHUD();

    bool isRunning();
    std::vector<std::string>& getArgv();

} // Game

} // Origin

#pragma once
#include "Core/Object.h"
#include <string>
#include <vector>

namespace Origin {

class Logger;
class Window;
class Settings;
class DebugEnvironment;
class Event;
class RenderManager;
class UIManager;
class EntityManager;
class ResourceManager;
class Overlay;
class Input;
class World;

class Game : public Object {

public:
    Game(int argc, char* argv[], Object* parent = nullptr);
    ~Game();

    // Path to Game directory
    static std::string getCurrentDirectory();

    void run();
    static void quit();

    static Logger* getLogger();
    static Window* getWindow();
    static Settings* getSettings();
    static RenderManager* getRenderManager();
    static UIManager* getUIManager();
    static EntityManager* getEntityManager();
    static DebugEnvironment* getDebugEnvironment();
    static Event* getEvent();
    static ResourceManager* getResourceManager();
    static Overlay* getOverlay();
    static Input* getInput();
    static World* getWorld();

    static bool isRunning();
    static std::vector<std::string>& getArgv();

private:
    void init();

    std::vector<std::string> argvs;
    static bool running;

    static Settings* settings;
    static Logger* logger;
    static DebugEnvironment* debugEnvironment;
    static Event* event;
    static Window* window;
    static RenderManager* renderManager;
    static UIManager* uiManager;
    static EntityManager* entityManager;
    static ResourceManager* resourceManager;
    static Overlay* overlay;
    static Input* input;
    static World* world;
};

} // Origin

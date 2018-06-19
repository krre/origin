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
    static bool isRunning();
    static std::vector<std::string>& getArgv();

private:
    void init();

    std::vector<std::string> argvs;
    static bool running;
};

} // Origin

#pragma once
#include <core/Object.h>
#include <string>
#include <vector>

class Game : public Core::Object {

public:
    static constexpr auto Name = "Origin";
    static constexpr auto Status = STATUS;
    static constexpr auto Version = VERSION;
    static constexpr auto Url = "https://github.com/krre/origin";
    static constexpr auto SettingsName = "settings.json";

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

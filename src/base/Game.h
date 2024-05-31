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
    static std::string currentDirectory();

    void run();
    static void quit();
    static bool isRunning();

private:
    void init();

    std::vector<std::string> args;
    static bool running;
};

#pragma once
#include <core/Object.h>
#include <string>
#include <vector>

class Game : public Core::Object {

public:
    static constexpr auto Name = NAME_STRING;
    static constexpr auto Status = STATUS_STRING;
    static constexpr auto Version = VERSION_STRING;
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

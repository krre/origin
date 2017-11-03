#pragma once
#include "Singleton.h"

class Game : public Singleton<Game> {

public:
    Game();

    void load();
    void save();
};

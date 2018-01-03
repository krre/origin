#pragma once
#include "Singleton.h"

namespace Origin {

class Game : public Singleton<Game> {

public:
    Game();

    void load();
    void save();
};

} // Origin

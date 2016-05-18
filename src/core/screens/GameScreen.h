#pragma once
#include "Screen.h"

class GameScreen : public Screen {

public:
    GameScreen();
    void update() override;
    void render() override;
};

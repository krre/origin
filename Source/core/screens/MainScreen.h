#pragma once
#include "Screen.h"

class MainScreen : public Screen {

public:
    MainScreen();
    void update() override;
    void render() override;
};

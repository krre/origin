#pragma once
#include "Core/Screen.h"

class MenuScreen : public Screen {

public:
    MenuScreen();

    void update(float dt) override;
    void render(float dt) override;
    void resize(uint32_t width, uint32_t height) override;
};

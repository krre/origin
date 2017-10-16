#pragma once
#include "Common.h"

class Screen {

public:
    Screen();
    virtual void hide();
    virtual void pause();
    virtual void resume();
    virtual void show();

    virtual void update(float dt) = 0;
    virtual void render(float dt) = 0;
    virtual void resize(uint32_t width, uint32_t height) = 0;
};

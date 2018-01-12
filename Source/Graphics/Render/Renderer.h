#pragma once
#include "Core/Common.h"

namespace Origin {

class Screen;

class Renderer {

public:
    Renderer();
    virtual ~Renderer();
    void render(Screen* screen);

protected:
    virtual void renderQueue() = 0;
};

} // Origin

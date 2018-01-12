#pragma once
#include "Core/Common.h"

namespace Origin {

class Screen;

class Renderer {

public:
    Renderer();
    virtual ~Renderer();
    void render(Screen* screen);
};

} // Origin

#pragma once
#include "Core/Common.h"

namespace Origin {

class Control;

class Renderer2D {

public:
    Renderer2D();
    virtual ~Renderer2D();
    void render(Control* control);
};

} // Origin

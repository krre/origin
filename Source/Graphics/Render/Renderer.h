#pragma once
#include "Core/Common.h"

namespace Origin {

class Screen;
class Renderer2D;

class Renderer {

public:
    Renderer();
    virtual ~Renderer();
    void render(Screen* screen);

protected:
    virtual void renderQueue() = 0;

private:
    std::unique_ptr<Renderer2D> renderer2d;
};

} // Origin

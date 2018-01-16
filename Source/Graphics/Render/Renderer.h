#pragma once
#include "Core/Common.h"

namespace Origin {

class Screen;
class Renderer2D;
class Renderer3D;

class Renderer {

public:
    Renderer();
    virtual ~Renderer();
    void render(Screen* screen);

protected:
    virtual void renderQueue() = 0;

private:
    std::unique_ptr<Renderer2D> renderer2d;
    std::unique_ptr<Renderer3D> renderer3d;
};

} // Origin

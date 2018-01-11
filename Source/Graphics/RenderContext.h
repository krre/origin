#pragma once
#include "Core/Singleton.h"

namespace Origin {

class RenderWindow;
class Renderer;

class RenderContext : public Singleton<RenderContext> {

public:
    RenderContext();
    ~RenderContext();
    virtual RenderWindow* createRenderWindow() = 0;
    virtual Renderer* createRenderer() = 0;

protected:

};

} // Origin

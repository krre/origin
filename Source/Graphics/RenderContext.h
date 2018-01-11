#pragma once
#include "Core/Singleton.h"

namespace Origin {

class RenderWindow;
class Renderer;

class RenderContext : public Singleton<RenderContext> {

public:
    RenderContext();
    ~RenderContext();
    virtual std::shared_ptr<RenderWindow> createRenderWindow() = 0;
    virtual std::shared_ptr<Renderer> createRenderer() = 0;

protected:

};

} // Origin

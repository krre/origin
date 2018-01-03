#pragma once
#include "Core/Singleton.h"

namespace Origin {

class RenderWindow;
class Renderer;

class GraphicsContext : public Singleton<GraphicsContext> {

public:
    GraphicsContext();
    ~GraphicsContext();
    virtual RenderWindow* createRenderWindow() = 0;
    virtual Renderer* createRenderer() = 0;

protected:

};

} // Origin

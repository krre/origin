#pragma once
#include "Core/Singleton.h"

class RenderWindow;

class GraphicsContext : public Singleton<GraphicsContext> {

public:
    GraphicsContext();
    ~GraphicsContext();
    virtual RenderWindow* createRenderWindow() = 0;

protected:
};

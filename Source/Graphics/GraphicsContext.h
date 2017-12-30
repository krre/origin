#pragma once
#include "Core/Singleton.h"

class RenderWindow;

class GraphicsContext : public Singleton<GraphicsContext> {

public:
    GraphicsContext();
    ~GraphicsContext();
    RenderWindow* createRenderWindow();
    RenderWindow* getRenderWindow() const { return renderWindow; }

protected:
    virtual RenderWindow* createRenderWindowImpl() = 0;

    RenderWindow* renderWindow = nullptr;
};

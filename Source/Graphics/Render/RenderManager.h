#pragma once

class RenderWindow;

class RenderManager {

public:
    RenderManager();
    virtual RenderWindow* createRenderWindow() = 0;
};

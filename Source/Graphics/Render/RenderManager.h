#pragma once
#include "Core/Singleton.h"

class RenderWindow;

class RenderManager : public Singleton<RenderManager> {

public:
    RenderManager();
    virtual RenderWindow* createRenderWindow() = 0;
};

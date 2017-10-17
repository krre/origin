#pragma once
#include "Core/Singleton.h"

class Screen;

class RenderManager : public Singleton<RenderManager> {

public:
    RenderManager();
    void clearScreen(Screen* screen);
};

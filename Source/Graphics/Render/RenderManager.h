#pragma once
#include "Core/Singleton.h"

class Screen;
class Scene;

class RenderManager : public Singleton<RenderManager> {

public:
    RenderManager();
    void clearScreen(Screen* screen);
    void renderScene(Scene* scene);
};

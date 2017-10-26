#pragma once
#include "Core/Singleton.h"

class Screen;
class View;

class RenderManager : public Singleton<RenderManager> {

public:
    RenderManager();
    void renderView(View* view);
};

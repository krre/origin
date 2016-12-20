#pragma once
#include "../UI/Viewport.h"

class Scene : public Viewport {

public:
    Scene();
    virtual void draw(float dt) = 0;
    virtual void update(float dt) = 0;
    virtual void create() = 0;
    bool getIsFullScreen() const { return isFullScreen; }

protected:
    virtual void onWindowResize(int width, int height) = 0;
    bool isFullScreen = true;
};

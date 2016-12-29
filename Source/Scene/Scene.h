#pragma once
#include "../UI/Viewport.h"
#include "../Graphics/Vulkan/Device.h"
#include <SDL.h>

class Scene : public Viewport {

public:
    Scene();
    ~Scene();
    virtual void init() {}
    virtual void create() {}
    virtual void cleanup() {}
    virtual void pause() {}
    virtual void resume() {}

    virtual void update(float dt) = 0;
    virtual void draw(float dt) = 0;

    bool getIsFullScreen() const { return isFullScreen; }

protected:
    virtual void onWindowResize(int width, int height) = 0;
    virtual void onKeyPressed(const SDL_KeyboardEvent& event) = 0;
    bool isFullScreen = true;
    Vulkan::Device* device = nullptr;
};

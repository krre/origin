#pragma once
#include "../System.h"
#include "../Graphics/Drawable.h"
#include "../Graphics/Renderer.h"
#include <vector>

class RenderSystem : public System {

public:
    RenderSystem();
    void process(float dt) override;

private:
    Renderer renderer;
    std::vector<Drawable*> drawables;
};

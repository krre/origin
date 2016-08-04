#pragma once
#include "../System.h"
#include "../Graphics/Drawable.h"
#include "../Graphics/Renderer.h"
#include "../Graphics/Voxel/RenderSurface.h"
#include <vector>

class RenderSystem : public System {

public:
    RenderSystem();
    void process(float dt) override;

private:
    RenderSurface renderSurface;
    Renderer renderer;
    std::vector<Drawable*> drawables;
};

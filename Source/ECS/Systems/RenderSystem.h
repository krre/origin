#pragma once
#include "../System.h"
#include "../Graphics/Drawable.h"
#include "../Graphics/Voxel/RenderSurface.h"
#include <vector>

class RenderSystem : public System {

public:
    RenderSystem();
    void process(float dt) override;

private:
    RenderSurface renderSurface;
    std::vector<Drawable*> drawables;
};

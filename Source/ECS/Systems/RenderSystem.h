#pragma once
#include "../System.h"
#include "../../Graphics/Drawable.h"
#include "../../Graphics/Voxel/RenderSurface.h"
#include <vector>

class RenderSystem : public System {

public:
    RenderSystem();
    void process(float dt) override;
    RenderSurface* getRenderSurface() { return &renderSurface; }

private:
    RenderSurface renderSurface;
    std::vector<CovenantLand::Drawable*> drawables;
};

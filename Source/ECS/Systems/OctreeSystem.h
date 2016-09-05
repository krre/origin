#pragma once
#include "../System.h"
#include "../Graphics/Drawable.h"
#include "../Graphics/Voxel/RenderSurface.h"
#include <vector>

class OctreeSystem : public System {

public:
    OctreeSystem();
    void process(float dt) override;
};

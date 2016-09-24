#pragma once
#include "../System.h"
#include "../../Graphics/Drawable.h"
#include "../../Graphics/Voxel/RenderSurface.h"
#include "../../Graphics/Voxel/SVOBuilder.h"
#include <vector>

class OctreeSystem : public System {

public:
    OctreeSystem();
    void process(float dt) override;
    SVOBuilder* getSVOBuilder() { return &svoBuilder; }

private:
    SVOBuilder svoBuilder;
};

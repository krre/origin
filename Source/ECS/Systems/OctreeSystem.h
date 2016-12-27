#pragma once
#include "../System.h"
#include "../../Graphics/Drawable.h"
#include "../../Graphics/Voxel/SVOBuilder.h"
#include "../../Graphics/Voxel/GPUMemoryManager.h"
#include <vector>

class OctreeSystem : public System {

public:
    OctreeSystem();
    void process(float dt) override;
    SVOBuilder* getSVOBuilder() { return &svoBuilder; }
    GPUMemoryManager* getGpuMemoryManager() { return &gpuMemoryManager; }

private:
    SVOBuilder svoBuilder;
    GPUMemoryManager gpuMemoryManager;
};

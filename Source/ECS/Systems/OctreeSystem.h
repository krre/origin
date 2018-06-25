#pragma once
#include "ECS/System.h"
#include "Graphics/Voxel/SVOBuilder.h"
#include "Graphics/Voxel/GPUMemoryManager.h"
#include <vector>

namespace Origin {

class OctreeSystem : public System {

public:
    OctreeSystem(EntityManager* entityManager);
    void process(float dt) override;
    SVOBuilder* getSVOBuilder() { return &svoBuilder; }
    GPUMemoryManager* getGpuMemoryManager() { return &gpuMemoryManager; }

private:
    SVOBuilder svoBuilder;
    GPUMemoryManager gpuMemoryManager;
};

} // Origin

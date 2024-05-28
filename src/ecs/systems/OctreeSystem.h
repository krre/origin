#pragma once
#include "ecs/System.h"
#include "graphics/voxel/SVOBuilder.h"
#include "graphics/voxel/GPUMemoryManager.h"

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

#pragma once
#include "ecs/System.h"
#include "graphics/voxel/SVOBuilder.h"
#include "graphics/voxel/GPUMemoryManager.h"

class OctreeSystem : public System {

public:
    OctreeSystem(EntityManager* entityManager);

    void process(float dt) override;
    SVOBuilder* svoBuilder() { return &m_svoBuilder; }
    GPUMemoryManager* gpuMemoryManager() { return &m_gpuMemoryManager; }

private:
    SVOBuilder m_svoBuilder;
    GPUMemoryManager m_gpuMemoryManager;
};

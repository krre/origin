#pragma once
#include "../System.h"
#include "../../Graphics/Drawable.h"
#include "../../Graphics/Voxel/RenderSurface.h"
#include "../../Graphics/Voxel/GPUMemoryManager.h"
#include <vector>

class RenderSystem : public System {

public:
    RenderSystem();
    void process(float dt) override;
    RenderSurface* getRenderSurface() { return &renderSurface; }
    GPUMemoryManager* getGpuMemoryManager() { return &gpuMemoryManager; }

private:
    RenderSurface renderSurface;
    GPUMemoryManager gpuMemoryManager;
    std::vector<Drawable*> drawables;
};

#pragma once
#include "Core/Singleton.h"
#include "GraphicsTypes.h"
#include <map>

namespace Vulkan {
    class GraphicsPipeline;
}

class Renderer : public Singleton<Renderer> {

public:
    Renderer();
    void render();
    Vulkan::GraphicsPipeline* getPipeline(PipelinePreset preset) const { return pipelines.at(preset).get(); }

private:
    std::map<PipelinePreset, std::shared_ptr<Vulkan::GraphicsPipeline>> pipelines;
};

#pragma once
#include "Core/Singleton.h"
#include "Graphics/GraphicsTypes.h"
#include <map>

namespace Origin {

namespace Vulkan {
    class GraphicsPipeline;
}

class RendererSet : public Singleton<RendererSet> {

public:
    RendererSet();
    void render();
    Vulkan::GraphicsPipeline* getPipeline(PipelinePreset preset) const { return pipelines.at(preset).get(); }

private:
    std::map<PipelinePreset, std::shared_ptr<Vulkan::GraphicsPipeline>> pipelines;
};

} // Origin

#pragma once
#include "RenderPassResource.h"

namespace Origin {

class RenderPassUI : public RenderPassResource {

public:
    RenderPassUI();
    void write(Vulkan::CommandBuffer* commandBuffer) override;
};

} // Origin

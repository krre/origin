#pragma once
#include "Core/Common.h"

namespace Vulkan {
    class CommandBuffer;
}

namespace Origin {

class RenderPassResource {

public:
    RenderPassResource();
    virtual void write(Vulkan::CommandBuffer* commandBuffer) = 0;
};

} // Origin

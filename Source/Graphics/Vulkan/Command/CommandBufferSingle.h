#pragma once
#include "CommandBuffers.h"
#include "CommandBuffer.h"

namespace Vulkan {

class CommandBufferSingle : public Devicer {

public:
    CommandBufferSingle(const Device* device);

private:
    std::shared_ptr<CommandBuffers> commandBuffers;
    std::shared_ptr<CommandBuffer> commandBuffer;
};

} // Vulkan

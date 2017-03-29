#pragma once
#include "CommandBuffers.h"
#include "CommandBuffer.h"
#include "../Fence.h"

namespace Vulkan {

class CommandBufferSingle : public Devicer {

public:
    CommandBufferSingle(const Device* device);
    void begin() { commandBuffer->begin(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT); }
    void end() { commandBuffer->end(); }

private:
    std::shared_ptr<CommandBuffers> commandBuffers;
    std::shared_ptr<CommandBuffer> commandBuffer;
    Fence fence;
};

} // Vulkan

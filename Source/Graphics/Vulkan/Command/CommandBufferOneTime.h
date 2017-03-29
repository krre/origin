#pragma once
#include "CommandBuffers.h"
#include "CommandBuffer.h"

namespace Vulkan {

class CommandBufferOneTime {

public:
    CommandBufferOneTime(Device* device);
    void apply();

    void begin() { commandBuffer->begin(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT); }
    void end() { commandBuffer->end(); }

private:
    Device* device;
    std::shared_ptr<CommandBuffers> commandBuffers;
    std::shared_ptr<CommandBuffer> commandBuffer;
};

} // Vulkan

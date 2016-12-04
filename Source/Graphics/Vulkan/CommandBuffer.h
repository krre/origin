#pragma once
#include "Base/Handle.h"
#include "Device.h"
#include "CommandPool.h"

namespace Vulkan {

class CommandBuffer : public Handle<VkCommandBuffer> {

public:
    CommandBuffer(VkCommandBuffer handle);
    bool create() override {}
    bool begin();
    bool end();

private:
    VkCommandBufferBeginInfo beginInfo = {};

};

} // Vulkan

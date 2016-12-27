#pragma once
#include "../Base/Handle.h"
#include "../Device.h"
#include "CommandPool.h"

namespace Vulkan {

class CommandBuffer : public Handle<VkCommandBuffer> {

public:
    CommandBuffer(VkCommandBuffer handle);
    VkResult create() override {}
    VkResult begin();
    VkResult end();

private:
    VkCommandBufferBeginInfo beginInfo = {};

};

} // Vulkan

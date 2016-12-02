#pragma once
#include "CreatableObject.h"
#include "Device.h"
#include "CommandPool.h"

namespace Vulkan {

class CommandBuffer : public CreatableObject<VkCommandBuffer> {

public:
    CommandBuffer(const Device* device);
    bool create() override {}
    void allocate(const CommandPool* commandPool, int count);
    int getCount() const { return commandBuffers.size(); }
    VkCommandBuffer getBuffer(int i) const { return commandBuffers.at(i); }
    VkCommandBuffer* getBuffers() { return commandBuffers.data(); }

private:
    const Device* device;
    std::vector<VkCommandBuffer> commandBuffers;
};

} // Vulkan

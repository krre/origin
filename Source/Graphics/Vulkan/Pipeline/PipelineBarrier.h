#pragma once
#include "Pipeline.h"
#include <vector>

namespace Vulkan {

class PipelineBarrier {

public:
    PipelineBarrier();
    uint32_t getMemoryBarrierCount() const { return memoryBarries.size(); }
    VkMemoryBarrier* getMemoryBarrierData() { return memoryBarries.data(); }

    uint32_t getBufferMemoryBarrierCount() const { return bufferMemoryBarries.size(); }
    VkBufferMemoryBarrier* getBufferMemoryBarrierData() { return bufferMemoryBarries.data(); }

    uint32_t getImageMemoryBarrierCount() const { return imageMemoryBarries.size(); }
    VkImageMemoryBarrier* getImageMemoryBarrierData() { return imageMemoryBarries.data(); }

    VkImageMemoryBarrier createImageMemoryBarrier();

private:
    std::vector<VkMemoryBarrier> memoryBarries;
    std::vector<VkBufferMemoryBarrier> bufferMemoryBarries;
    std::vector<VkImageMemoryBarrier> imageMemoryBarries;
};

} // Vulkan

#pragma once
#include "Pipeline.h"
#include <vector>

namespace Vulkan {

class PipelineBarrier {

public:
    PipelineBarrier();
    uint32_t getMemoryBarrierCount() const { return memoryBarriers.size(); }
    VkMemoryBarrier* getMemoryBarrierData() { return memoryBarriers.data(); }

    uint32_t getBufferMemoryBarrierCount() const { return bufferMemoryBarriers.size(); }
    VkBufferMemoryBarrier* getBufferMemoryBarrierData() { return bufferMemoryBarriers.data(); }

    void addImageMemoryBarrier(VkImageMemoryBarrier imageMemoryBarrier);
    uint32_t getImageMemoryBarrierCount() const { return imageMemoryBarriers.size(); }
    VkImageMemoryBarrier* getImageMemoryBarrierData() { return imageMemoryBarriers.data(); }

    static VkImageMemoryBarrier createImageMemoryBarrier();

private:
    std::vector<VkMemoryBarrier> memoryBarriers;
    std::vector<VkBufferMemoryBarrier> bufferMemoryBarriers;
    std::vector<VkImageMemoryBarrier> imageMemoryBarriers;
};

} // Vulkan

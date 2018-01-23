#pragma once
#include "../Base/Handle.h"
#include "../Device/Devicer.h"
#include <vector>

namespace Origin {

namespace Vulkan {

class DescriptorPool : public Handle<VkDescriptorPool>, public Devicer {

public:
    DescriptorPool(Device* device);
    ~DescriptorPool();
    void addPoolSize(VkDescriptorType type, uint32_t count);
    void create() override;
    void destroy() override;
    void reset();

private:
    VkDescriptorPoolCreateInfo createInfo = {};
    std::vector<VkDescriptorPoolSize> poolSizes;
};

} // Vulkan

} // Origin

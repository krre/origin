#pragma once
#include "../Base/Handle.h"
#include "../Device/Devicer.h"
#include <vector>

namespace Vulkan {

class DescriptorPool : public Handle<VkDescriptorPool>, public Devicer {

public:
    DescriptorPool(const Device* device);
    ~DescriptorPool();
    void addPoolSize(VkDescriptorType type, uint32_t count);
    VkResult create() override;
    void destroy() override;

    VkDescriptorPoolCreateInfo createInfo = {};

private:
    std::vector<VkDescriptorPoolSize> poolSizes;
};

} // Vulkan

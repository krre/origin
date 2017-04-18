#pragma once
#include "Graphics/Vulkan/Base/Handle.h"
#include "Graphics/Vulkan/Device/Devicer.h"
#include <vector>

namespace Vulkan {

class DescriptorPool : public Handle<VkDescriptorPool>, public Devicer {

public:
    DescriptorPool(Device* device = nullptr);
    ~DescriptorPool();
    void addPoolSize(VkDescriptorType type, uint32_t count);
    void create() override;
    void destroy() override;

private:
    VkDescriptorPoolCreateInfo createInfo = {};
    std::vector<VkDescriptorPoolSize> poolSizes;
};

} // Vulkan

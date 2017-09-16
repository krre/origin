#pragma once
#include "Graphics/Render/Vulkan/Wrapper/Base/Handle.h"
#include "Graphics/Render/Vulkan/Wrapper/Device/Devicer.h"
#include <vector>

namespace Vulkan {

class DescriptorPool : public Handle<VkDescriptorPool>, public Devicer {

public:
    DescriptorPool(Device* device = nullptr);
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

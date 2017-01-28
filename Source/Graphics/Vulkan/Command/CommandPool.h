#pragma once
#include "../Device/Devicer.h"

namespace Vulkan {

class CommandPool : public Devicer<VkCommandPool> {

public:
    CommandPool(const Device* device, uint32_t familyIndex);
    ~CommandPool();
    VkResult create() override;
    void destroy() override;
    VkResult reset();

private:
    VkCommandPoolCreateInfo createInfo = {};
};

} // Vulkan

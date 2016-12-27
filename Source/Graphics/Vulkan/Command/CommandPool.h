#pragma once
#include "../Base/Handle.h"
#include "../Device.h"

namespace Vulkan {

class CommandPool : public Handle<VkCommandPool> {

public:
    CommandPool(const Device* device, uint32_t familyIndex);
    ~CommandPool();
    VkResult create() override;
    VkResult reset();

private:
    const Device* device;
    VkCommandPoolCreateInfo createInfo;
};

} // Vulkan

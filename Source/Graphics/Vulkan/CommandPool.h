#pragma once
#include "CreatableObject.h"
#include "Device.h"

namespace Vulkan {

class CommandPool : public CreatableObject<VkCommandPool> {

public:
    CommandPool(const Device* device, uint32_t familyIndex);
    ~CommandPool();
    bool create() override;
    bool reset();

private:
    const Device* device;
    VkCommandPoolCreateInfo createInfo;
};

} // Vulkan

#pragma once
#include "VkCreatableObject.h"
#include "Device.h"

namespace Vulkan {

class CommandPool : public VkCreatableObject<VkCommandPool> {

public:
    CommandPool(const Device* device);
    ~CommandPool();
    void create() override;
    bool reset();

private:
    const Device* device;
    VkCommandPoolCreateInfo createInfo;
};

} // Vulkan

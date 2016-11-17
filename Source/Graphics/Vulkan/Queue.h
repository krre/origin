#pragma once
#include "VulkanObject.h"
#include "Device.h"
#include <vulkan/vulkan.h>

namespace Vulkan {

class Queue : public VulkanObject {

public:
    Queue(const Device* device);
    bool isValid() const { return handle != VK_NULL_HANDLE; }
    VkQueue getHandle() const { return handle; }

private:
    VkQueue handle = VK_NULL_HANDLE;
    const Device* device;
};

} // Vulkan

#pragma once
#include "Device.h"
#include "DeviceMemory.h"

namespace Vulkan {

class Image : public Handle<VkImage> {

public:
    Image(const Device* device, uint32_t width, uint32_t height);
    ~Image();
    VkResult create() override;
    DeviceMemory* getMemory() { return &memory; }

private:
    const Device* device;
    DeviceMemory memory;
    VkImageCreateInfo createInfo = {};
};

} // Vulkan

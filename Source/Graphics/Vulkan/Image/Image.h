#pragma once
#include "Graphics/Vulkan/Base/Handle.h"
#include "Graphics/Vulkan/Device/Devicer.h"

namespace Vulkan {

class DeviceMemory;

class Image : public Handle<VkImage>, public Devicer {

public:
    Image(Device* device);
    Image(Device* device, VkImage image);
    ~Image();
    void create() override;
    void destroy() override;
    DeviceMemory* getMemory() { return memory.get(); }

    void setWidth(uint32_t width);
    uint32_t getWidth() const { return createInfo.extent.width; }

    void setHeight(uint32_t height);
    uint32_t getHeight() const { return createInfo.extent.height; }

    void setFormat(VkFormat format);
    VkFormat getFormat() const { return createInfo.format; }

    void setUsage(VkImageUsageFlags usage);
    void setInitialLayout(VkImageLayout initialLayout);
    void write(void* data, VkDeviceSize size, VkDeviceSize offset = 0);

private:
    VkImageCreateInfo createInfo = {};
    std::unique_ptr<DeviceMemory> memory;
};

} // Vulkan

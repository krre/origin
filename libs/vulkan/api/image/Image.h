#pragma once
#include "../base/Handle.h"
#include "../device/Devicer.h"
#include <memory>

namespace Vulkan {

class DeviceMemory;

class Image : public Handle<VkImage>, public Devicer {

public:
    Image(Device* device);
    Image(Device* device, VkImage image);
    ~Image();

    void create() override;
    void destroy() override;

    DeviceMemory* memory() { return m_memory.get(); }

    void setWidth(uint32_t width);
    uint32_t width() const { return createInfo.extent.width; }

    void setHeight(uint32_t height);
    uint32_t height() const { return createInfo.extent.height; }

    void setFormat(VkFormat format);
    VkFormat format() const { return createInfo.format; }

    void setUsage(VkImageUsageFlags usage);
    void setTiling(VkImageTiling tiling);
    void setInitialLayout(VkImageLayout initialLayout);
    void write(void* data, VkDeviceSize size, VkDeviceSize offset = 0);

private:
    VkImageCreateInfo createInfo = {};
    std::unique_ptr<DeviceMemory> m_memory;
};

}

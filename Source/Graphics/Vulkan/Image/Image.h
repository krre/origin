#pragma once
#include "../Base/Handle.h"
#include "../Device/Devicer.h"
#include "../Device/DeviceMemory.h"
#include "../Sampler.h"

namespace Vulkan {

class Image : public Handle<VkImage>, public Devicer {

public:
    Image(Device* device = nullptr);
    ~Image();
    void create() override;
    void destroy() override;
    DeviceMemory* getMemory() { return &memory; }

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
    DeviceMemory memory;
};

} // Vulkan

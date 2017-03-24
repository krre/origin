#pragma once
#include "../Base/Handle.h"
#include "../Device/Devicer.h"
#include "../Device/DeviceMemory.h"
#include "../Sampler.h"

namespace Vulkan {

class Image : public Handle<VkImage>, public Devicer {

public:
    Image(const Device* device);
    ~Image();
    VkResult create() override;
    void destroy() override;
    DeviceMemory* getMemory() { return &memory; }
    void setWidth(uint32_t width);
    uint32_t getWidth() const { return createInfo.extent.width; }
    uint32_t getHeight() const { return createInfo.extent.height; }
    void setHeight(uint32_t height);
    void setFormat(VkFormat format);
    void setUsage(VkImageUsageFlags usage);
    void setInitialLayout(VkImageLayout initialLayout);
    VkFormat getFormat() const { return createInfo.format; }
    void write(void* data, VkDeviceSize count, VkDeviceSize offset = 0);

private:
    VkImageCreateInfo createInfo = {};
    VkMemoryRequirements memRequirements;
    DeviceMemory memory;
};

} // Vulkan

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
    void setHeight(uint32_t height);
    void setFormat(VkFormat format);
    void setUsage(VkImageUsageFlags usage);
    VkFormat getFormat() const { return createInfo.format; }

    VkImageCreateInfo createInfo = {};
    VkMemoryRequirements memRequirements;

private:
    DeviceMemory memory;
};

} // Vulkan

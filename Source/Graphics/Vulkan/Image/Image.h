#pragma once
#include "../Base/Handle.h"
#include "../Device/Devicer.h"
#include "../Device/DeviceMemory.h"
#include "../Sampler.h"
#include "../Image/ImageView.h"


namespace Vulkan {

class Image : public Handle<VkImage>, public Devicer {

public:
    Image(const Device* device);
    ~Image();
    VkResult create() override;
    void destroy() override;
    DeviceMemory* getMemory() { return &memory; }

    VkImageCreateInfo createInfo = {};
    VkDescriptorImageInfo descriptorInfo = {};

private:
    DeviceMemory memory;
};

} // Vulkan

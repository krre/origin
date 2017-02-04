#pragma once
#include "../Base/Handle.h"
#include "../Device/Devicer.h"
#include "../Device/DeviceMemory.h"
#include "../Sampler.h"
#include "../Image/ImageView.h"


namespace Vulkan {

class Image : public Handle<VkImage>, public Devicer {

public:
    Image(const Device* device, uint32_t width, uint32_t height);
    ~Image();
    VkResult create() override;
    void destroy() override;
    DeviceMemory* getMemory() { return &memory; }
    VkDescriptorImageInfo* getDescriptorInfo() { return &descriptorInfo; }
    void setFormat(VkFormat format);
    void setSampler(Sampler* sampler);
    void setImageView(ImageView* imageView);
    void setImageLayout(VkImageLayout imageLayout);

private:
    DeviceMemory memory;
    VkImageCreateInfo createInfo = {};
    VkDescriptorImageInfo descriptorInfo = {};
    Sampler* sampler = nullptr;
    ImageView* imageView = nullptr;
};

} // Vulkan

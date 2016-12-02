#pragma once
#include "Device.h"
#include "Surface.h"

namespace Vulkan {

class ImageView : public CreatableObject<VkImageView> {

public:
    ImageView(const Device* device, const Surface* surface, VkImage image);
    ~ImageView();
    bool create() override;

private:
    const Device* device;
    const Surface* surface;
    VkImageViewCreateInfo createInfo = {};
};

} // Vulkan

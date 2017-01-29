#pragma once
#include "../Base/Handle.h"
#include "../Device/Devicer.h"
#include "../Surface.h"

namespace Vulkan {

class ImageView : public Handle<VkImageView>, public Devicer {

public:
    ImageView(const Device* device, const Surface* surface, VkImage image);
    ~ImageView();
    VkResult create() override;
    void destroy() override;

private:
    const Surface* surface;
    VkImageViewCreateInfo createInfo = {};
};

} // Vulkan

#pragma once
#include "../base/Handle.h"
#include "../device/Devicer.h"

namespace Vulkan {

class ImageView : public Handle<VkImageView>, public Devicer {

public:
    ImageView(Device* device, VkImage image);
    ~ImageView();
    void create() override;
    void destroy() override;
    void setFormat(VkFormat format);
    void setAspectMask(VkImageAspectFlags aspectMask);

private:
    VkImageViewCreateInfo createInfo = {};
};

}

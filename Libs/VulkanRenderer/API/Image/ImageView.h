#pragma once
#include "../Base/Handle.h"
#include "../Device/Devicer.h"

namespace Origin {

namespace Vulkan {

class ImageView : public Handle<VkImageView>, public Devicer {

public:
    ImageView(Device* device, VkImage image);
    ~ImageView();
    void create() override;
    void destroy() override;
    void setFormat(VkFormat format);

private:
    VkImageViewCreateInfo createInfo = {};
};

} // Vulkan

} // Origin

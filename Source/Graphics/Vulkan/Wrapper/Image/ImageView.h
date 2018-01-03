#pragma once
#include "Graphics/Vulkan/Wrapper/Base/Handle.h"
#include "Graphics/Vulkan/Wrapper/Device/Devicer.h"

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

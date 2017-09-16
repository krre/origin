#pragma once
#include "Graphics/Render/Vulkan/Wrapper/Base/Handle.h"
#include "Graphics/Render/Vulkan/Wrapper/Device/Devicer.h"

namespace Vulkan {

class ImageView : public Handle<VkImageView>, public Devicer {

public:
    ImageView(VkImage image, Device* device = nullptr);
    ~ImageView();
    void create() override;
    void destroy() override;
    void setFormat(VkFormat format);

private:
    VkImageViewCreateInfo createInfo = {};
};

} // Vulkan

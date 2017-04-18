#pragma once
#include "Graphics/Vulkan/Base/Handle.h"
#include "Graphics/Vulkan/Device/Devicer.h"
#include "Graphics/Vulkan/Surface.h"

namespace Vulkan {

class ImageView : public Handle<VkImageView>, public Devicer {

public:
    ImageView(VkImage image, Device* device = nullptr);
    ~ImageView();
    void create() override;
    void destroy() override;

    VkImageViewCreateInfo createInfo = {};
};

} // Vulkan

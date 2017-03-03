#pragma once
#include "../Base/Handle.h"
#include "../Device/Devicer.h"

namespace Vulkan {

class CommandPool : public Handle<VkCommandPool>, public Devicer {

public:
    CommandPool(const Device* device, uint32_t familyIndex);
    ~CommandPool();
    VkResult create() override;
    void destroy() override;
    VkResult reset();

    VkCommandPoolCreateInfo createInfo = {};
};

} // Vulkan

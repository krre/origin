#pragma once
#include "../Base/Handle.h"
#include "../Device/Devicer.h"

namespace Vulkan {

class CommandPool : public Handle<VkCommandPool>, public Devicer {

public:
    CommandPool(uint32_t familyIndex, Device* device = nullptr);
    ~CommandPool();
    void create() override;
    void destroy() override;
    VkResult reset();

    VkCommandPoolCreateInfo createInfo = {};
};

} // Vulkan

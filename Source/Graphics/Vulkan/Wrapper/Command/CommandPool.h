#pragma once
#include "Graphics/Vulkan/Wrapper/Base/Handle.h"
#include "Graphics/Vulkan/Wrapper/Device/Devicer.h"

namespace Vulkan {

class CommandPool : public Handle<VkCommandPool>, public Devicer {

public:
    CommandPool(uint32_t familyIndex, Device* device = nullptr);
    ~CommandPool();
    void create() override;
    void destroy() override;
    void reset();

private:
    VkCommandPoolCreateInfo createInfo = {};
};

} // Vulkan

#pragma once
#include "Graphics/Vulkan/Wrapper/Base/Handle.h"
#include "Graphics/Vulkan/Wrapper/Device/Devicer.h"

namespace Origin {

namespace Vulkan {

class CommandPool : public Handle<VkCommandPool>, public Devicer {

public:
    CommandPool(Device* device, uint32_t queueFamilyIndex);
    ~CommandPool();
    void create() override;
    void destroy() override;
    void reset();

    uint32_t getQueueFamilyIndex() const { return createInfo.queueFamilyIndex; }

private:
    VkCommandPoolCreateInfo createInfo = {};
};

} // Vulkan

} // Origin

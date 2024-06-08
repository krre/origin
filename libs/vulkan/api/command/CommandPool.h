#pragma once
#include "../base/Handle.h"
#include "../device/Devicer.h"

namespace Vulkan {

class CommandPool : public Handle<VkCommandPool>, public Devicer {

public:
    CommandPool(Device* device, uint32_t queueFamilyIndex);
    ~CommandPool();

    void create() override;
    void destroy() override;

    void reset();

    uint32_t getQueueFamilyIndex() const { return m_createInfo.queueFamilyIndex; }

private:
    VkCommandPoolCreateInfo m_createInfo = {};
};

}

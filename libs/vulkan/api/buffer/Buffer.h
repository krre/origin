#pragma once
#include "../base/Handle.h"
#include "../device/Devicer.h"

namespace Vulkan {

class Buffer : public Handle<VkBuffer>, public Devicer {

public:
    Buffer(Device* device, VkBufferUsageFlagBits usage, VkDeviceSize size);
    ~Buffer();

    void create() override;
    void destroy() override;

    VkDeviceSize size() const { return m_createInfo.size; }

private:
    VkBufferCreateInfo m_createInfo = {};
};

}

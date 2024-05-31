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
    VkDeviceSize getSize() const { return createInfo.size; }

private:
    VkBufferCreateInfo createInfo = {};
};

}

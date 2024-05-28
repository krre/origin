#pragma once
#include "base/Handle.h"
#include "device/Devicer.h"

namespace Vulkan {

class QueryPool : public Handle<VkQueryPool>, public Devicer {

public:
    QueryPool(Device* device);
    ~QueryPool();
    void create() override;
    void destroy() override;

private:
    VkQueryPoolCreateInfo createInfo = {};
};

} // Vulkan

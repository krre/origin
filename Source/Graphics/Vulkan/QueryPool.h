#pragma once
#include "Base/Handle.h"
#include "Device/Devicer.h"

namespace Vulkan {

class QueryPool : public Handle<VkQueryPool>, public Devicer {

public:
    QueryPool(Device* device = nullptr);
    ~QueryPool();
    void create() override;
    void destroy() override;

private:
    VkQueryPoolCreateInfo createInfo = {};
};

} // Vulkan

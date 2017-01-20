#pragma once
#include "Base/Handle.h"
#include "Device/Device.h"

namespace Vulkan {

class Event : public Handle<VkEvent> {

public:
    Event(const Device* device);
    ~Event();
    VkResult create() override;

private:
    const Device* device;
    VkEventCreateInfo createInfo = {};
};

} // Vulkan

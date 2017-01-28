#pragma once
#include "Device/Devicer.h"

namespace Vulkan {

class Event : public Devicer<VkEvent> {

public:
    Event(const Device* device);
    ~Event();
    VkResult create() override;

private:
    VkEventCreateInfo createInfo = {};
};

} // Vulkan

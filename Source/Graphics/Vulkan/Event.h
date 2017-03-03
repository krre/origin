#pragma once
#include "Base/Handle.h"
#include "Device/Devicer.h"

namespace Vulkan {

class Event : public Handle<VkEvent>, public Devicer {

public:
    Event(const Device* device);
    ~Event();
    VkResult create() override;

    VkEventCreateInfo createInfo = {};
};

} // Vulkan

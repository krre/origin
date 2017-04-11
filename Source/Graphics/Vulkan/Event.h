#pragma once
#include "Base/Handle.h"
#include "Device/Devicer.h"

namespace Vulkan {

class Event : public Handle<VkEvent>, public Devicer {

public:
    Event(Device* device = nullptr);
    ~Event();
    void create() override;

    VkEventCreateInfo createInfo = {};
};

} // Vulkan

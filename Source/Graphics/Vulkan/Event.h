#pragma once
#include "Base/Handle.h"
#include "Device/Devicer.h"

namespace Origin {

namespace Vulkan {

class Event : public Handle<VkEvent>, public Devicer {

public:
    Event(Device* device);
    ~Event();
    void create() override;

private:
    VkEventCreateInfo createInfo = {};
};

} // Vulkan

} // Origin

#pragma once
#include "base/Handle.h"
#include "device/Devicer.h"

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

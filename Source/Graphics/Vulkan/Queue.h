#pragma once
#include "CreatableObject.h"
#include "Device.h"

namespace Vulkan {

class Queue : public CreatableObject<VkQueue> {

public:
    Queue(const Device* device);
    bool create() override;

private:
    const Device* device;
};

} // Vulkan

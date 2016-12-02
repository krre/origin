#pragma once
#include "VkCreatableObject.h"
#include "Device.h"

namespace Vulkan {

class Queue : public VkCreatableObject<VkQueue> {

public:
    Queue(const Device* device);
    void create() override;

private:
    const Device* device;
};

} // Vulkan

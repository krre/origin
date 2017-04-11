#pragma once
#include "Base/Handle.h"
#include "Device/Devicer.h"

namespace Vulkan {

class Semaphore : public Handle<VkSemaphore>, public Devicer {

public:
    Semaphore(Device* device = nullptr);
    ~Semaphore();
    void create() override;
    void destroy() override;

private:
    VkSemaphoreCreateInfo createInfo = {};
};

} // Vulkan

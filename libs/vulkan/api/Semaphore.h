#pragma once
#include "base/Handle.h"
#include "device/Devicer.h"

namespace Vulkan {

class Semaphore : public Handle<VkSemaphore>, public Devicer {
public:
    Semaphore(Device* device);
    ~Semaphore();

    void create() override;

private:
    VkSemaphoreCreateInfo m_createInfo = {};
};

}

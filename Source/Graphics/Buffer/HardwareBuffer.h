#pragma once
#include "Core/Object.h"
#include <vulkan/vulkan.h>

namespace Vulkan {
    class Buffer;
}

class HardwareBuffer : public Object {

public:
    HardwareBuffer();
    ~HardwareBuffer();
    VkBuffer getHandle() const; // TODO: Hide from common access

protected:
    std::unique_ptr<Vulkan::Buffer> buffer;
    std::unique_ptr<Vulkan::Buffer> stageBuffer; // TODO: Use for staging

private:

};

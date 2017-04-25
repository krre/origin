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
    VkBuffer getHandle() const;
    void write(const void* data, uint64_t size, uint64_t offset = 0);
    void read(void* data, uint64_t size, uint64_t offset = 0);

protected:
    std::unique_ptr<Vulkan::Buffer> buffer;
    std::unique_ptr<Vulkan::Buffer> stageBuffer; // TODO: Use for staging

private:

};

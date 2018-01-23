#pragma once
#include "Core/Object.h"
#include <vulkan/vulkan.h>

namespace Vulkan {
    class CommandPool;
    class Buffer;
    class DeviceMemory;
}

namespace Origin {

class HardwareBuffer : public Object {

public:
    HardwareBuffer();
    ~HardwareBuffer();
    VkBuffer getHandle() const;

    void write(const void* data, VkDeviceSize size, VkDeviceSize offset = 0);
    void read(void* data, VkDeviceSize size, VkDeviceSize offset = 0);
//    void copyToBuffer(Vulkan::CommandPool* commandPool, Vulkan::Buffer* dstBuffer, VkDeviceSize size);

protected:
    void bindMemory();
    std::unique_ptr<Vulkan::Buffer> buffer;
//    std::unique_ptr<Vulkan::DeviceMemory> memory;
    std::unique_ptr<Vulkan::Buffer> stageBuffer; // TODO: Use for staging

private:

};

} // Origin

#pragma once
#include "Base/Handle.h"
#include "Device/Devicer.h"
#include "Device/DeviceMemory.h"

namespace Vulkan {

class Buffer : public Handle<VkBuffer>, public Devicer {

public:

    Buffer(const Device* device, VkBufferUsageFlagBits usage, VkDeviceSize size, bool moveToDevice = true);
    ~Buffer();
    void create() override;
    void destroy() override;
    VkDeviceSize getSize() const { return createInfo.size; }
    void write(VkDeviceSize offset, VkDeviceSize size, const void* data);
    void read(VkDeviceSize offset, VkDeviceSize size, void* data);
    void copy(VkBuffer dstBuffer, VkDeviceSize size);

    VkDescriptorBufferInfo descriptorInfo = {};

private:
    VkBufferCreateInfo createInfo = {};
    DeviceMemory memory;
    bool moveToDevice;
};

} // Vulkan

#pragma once
#include "Base/Handle.h"
#include "Device/Devicer.h"
#include "Device/DeviceMemory.h"

namespace Vulkan {

class Buffer : public Handle<VkBuffer>, public Devicer {

public:

    enum class Type {
        VERTEX,
        INDEX,
        UNIFORM,
        STORAGE,
        TRANSFER_SRC,
        TRANSFER_DST
    };

    enum class Destination {
        HOST,
        DEVICE
    };

    Buffer(const Device* device, VkBufferUsageFlagBits usage, VkDeviceSize size);
    Buffer(const Device* device, VkDeviceSize size, Type type, Destination destination = Destination::HOST);
    ~Buffer();
    VkResult create() override;
    void destroy() override;
    VkDeviceSize getSize() const { return createInfo.size; }
    void write(VkDeviceSize offset, VkDeviceSize size, const void* data);
    void read(VkDeviceSize offset, VkDeviceSize size, void* data);
    VkDescriptorBufferInfo* getDescriptorInfo() { return &descriptorInfo; }
    void copy(VkBuffer dstBuffer, VkDeviceSize size);

    VkBufferCreateInfo createInfo = {};
    VkDescriptorBufferInfo descriptorInfo = {};

private:
    DeviceMemory memory;
    Destination destination;
};

} // Vulkan

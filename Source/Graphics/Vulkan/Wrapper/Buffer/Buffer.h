#pragma once
#include "Graphics/Vulkan/Wrapper/Base/Handle.h"
#include "Graphics/Vulkan/Wrapper/Device/Devicer.h"

namespace Vulkan {

class DeviceMemory;

class Buffer : public Handle<VkBuffer>, public Devicer {

public:

    Buffer(Device* device, VkBufferUsageFlagBits usage, VkDeviceSize size, bool moveToDevice = true);
    ~Buffer();
    void create() override;
    void destroy() override;
    VkDeviceSize getSize() const { return createInfo.size; }
    void write(const void* data, VkDeviceSize size, VkDeviceSize offset = 0);
    void read(void* data, VkDeviceSize size, VkDeviceSize offset = 0);
    void copyToBuffer(VkBuffer dstBuffer, VkDeviceSize size);
    const VkDescriptorBufferInfo* getDescriptorInfo() const { return &descriptorInfo; }

private:
    VkBufferCreateInfo createInfo = {};
    VkDescriptorBufferInfo descriptorInfo = {};
    std::unique_ptr<DeviceMemory> memory;
    bool moveToDevice;
};

} // Vulkan

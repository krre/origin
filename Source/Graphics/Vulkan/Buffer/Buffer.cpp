#include "Buffer.h"
#include "Graphics/Vulkan/Device/DeviceMemory.h"
#include "Graphics/Vulkan/Queue/SubmitQueue.h"
#include "Graphics/Vulkan/Command/CommandBufferOneTime.h"
#include <string.h>

using namespace Vulkan;

Buffer::Buffer(VkBufferUsageFlagBits usage, VkDeviceSize size, bool moveToDevice, Device* device) :
        Devicer(device), moveToDevice(moveToDevice) {
    memory = std::unique_ptr<DeviceMemory>(new DeviceMemory(device));

    createInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    createInfo.size = size;
    createInfo.usage = usage;
    createInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (moveToDevice) {
        createInfo.usage |= VK_BUFFER_USAGE_TRANSFER_DST_BIT;
    }
}

Buffer::~Buffer() {
    destroy();
}

void Buffer::create() {
    VULKAN_CHECK_RESULT(vkCreateBuffer(device->getHandle(), &createInfo, nullptr, &handle), "Failed to create buffer");
    descriptorInfo.buffer = handle;
    if (!descriptorInfo.range) {
        descriptorInfo.range = createInfo.size;
    }

    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(device->getHandle(), handle, &memRequirements);
    VkMemoryPropertyFlags properties = !moveToDevice ?
                (VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT) :
                VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
    memory->setMemoryTypeIndex(device->getPhysicalDevice()->findMemoryType(memRequirements.memoryTypeBits, properties));
    memory->allocate(memRequirements.size);

    vkBindBufferMemory(device->getHandle(), handle, memory->getHandle(), 0);
}

void Buffer::destroy() {
    VULKAN_DESTROY_HANDLE(vkDestroyBuffer(device->getHandle(), handle, nullptr))
}

void Buffer::write(const void* data, VkDeviceSize size, VkDeviceSize offset) {
    void* mapData;
    memory->map(&mapData, size, offset);
    memcpy(mapData, data, size);
    memory->unmap();
}

void Buffer::read(void* data, VkDeviceSize size, VkDeviceSize offset) {
    void* mapData;
    memory->map(&mapData, size, offset);
    memcpy(data, mapData, size);
    memory->unmap();
}

void Buffer::copyToBuffer(VkBuffer dstBuffer, VkDeviceSize size) {
    CommandBufferOneTime commandBuffer(const_cast<Device*>(device));

    VkBufferCopy bufferCopy = {};
    bufferCopy.size = size;
    commandBuffer.addBufferCopy(bufferCopy);
    commandBuffer.copyBuffer(handle, dstBuffer);

    commandBuffer.apply();
}

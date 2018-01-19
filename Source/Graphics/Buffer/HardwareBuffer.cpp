#include "HardwareBuffer.h"
#include "Graphics/Vulkan/Buffer/Buffer.h"
#include "Graphics/Vulkan/Device/DeviceMemory.h"
#include "Graphics/Vulkan/Device/PhysicalDevice.h"
#include "Graphics/Vulkan/Queue.h"
#include "Graphics/Vulkan/Command/CommandBufferOneTime.h"
#include <string.h>

namespace Origin {

HardwareBuffer::HardwareBuffer() {

}

HardwareBuffer::~HardwareBuffer() {

}

VkBuffer HardwareBuffer::getHandle() const {
    return buffer->getHandle();
}

void HardwareBuffer::write(const void* data, VkDeviceSize size, VkDeviceSize offset) {
    void* mapData;
    memory->map(&mapData, size, offset);
    memcpy(mapData, data, size);
    memory->unmap();
}

void HardwareBuffer::read(void* data, VkDeviceSize size, VkDeviceSize offset) {
    void* mapData;
    memory->map(&mapData, size, offset);
    memcpy(data, mapData, size);
    memory->unmap();
}

void HardwareBuffer::copyToBuffer(Vulkan::CommandPool* commandPool, Vulkan::Buffer* dstBuffer, VkDeviceSize size ){
    Vulkan::CommandBufferOneTime commandBuffer(buffer->getDevice(), commandPool);

    VkBufferCopy bufferCopy = {};
    bufferCopy.size = size;
    commandBuffer.addBufferCopy(bufferCopy);
    commandBuffer.copyBuffer(buffer->getHandle(), dstBuffer->getHandle());

    commandBuffer.apply();
}

void HardwareBuffer::bindMemory() {
    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(buffer->getDevice()->getHandle(), buffer->getHandle(), &memRequirements);
    bool moveToDevice = false; // TODO: Pass to constructor
    VkMemoryPropertyFlags properties = !moveToDevice ?
                (VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT) :
                VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
    memory->setMemoryTypeIndex(buffer->getDevice()->getPhysicalDevice()->findMemoryType(memRequirements.memoryTypeBits, properties));
    memory->allocate(memRequirements.size);

    vkBindBufferMemory(buffer->getDevice()->getHandle(), buffer->getHandle(), memory->getHandle(), 0);
}

} // Origin

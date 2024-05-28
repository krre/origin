#include "GpuBuffer.h"
#include "api/buffer/Buffer.h"
#include "api/device/DeviceMemory.h"
#include "api/device/PhysicalDevice.h"
#include "api/command/CommandBufferOneTime.h"
#include "Renderer.h"
#include <cstring>

namespace Vulkan {

GpuBuffer::GpuBuffer(Device* device, VkBufferUsageFlagBits usage, uint32_t size) :
        usage(usage),
        size(size) {
    buffer = std::make_unique<Buffer>(device, usage, size);
    buffer->create();

    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(buffer->getDevice()->getHandle(), buffer->getHandle(), &memRequirements);
    bool moveToDevice = false; // TODO: Pass to constructor
    VkMemoryPropertyFlags properties = !moveToDevice ?
                (VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT) :
                VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
    memory = std::make_unique<DeviceMemory>(device);
    memory->setMemoryTypeIndex(buffer->getDevice()->getPhysicalDevice()->findMemoryType(memRequirements.memoryTypeBits, properties));
    memory->allocate(memRequirements.size);

    vkBindBufferMemory(buffer->getDevice()->getHandle(), buffer->getHandle(), memory->getHandle(), 0);
}

GpuBuffer::~GpuBuffer() {

}

VkBuffer GpuBuffer::getHandle() const {
    return buffer->getHandle();
}

void GpuBuffer::copyToBuffer(Buffer* dstBuffer, VkDeviceSize size) {
//    CommandBufferOneTime commandBuffer(buffer->getDevice(), Game::getRenderManager->getComputeCommandPool());

    VkBufferCopy bufferCopy = {};
    bufferCopy.size = size;
//    commandBuffer.addBufferCopy(bufferCopy);
//    commandBuffer.copyBuffer(buffer->getHandle(), dstBuffer->getHandle());

//    commandBuffer.apply();
}

void GpuBuffer::write(const void* data, uint32_t size, uint32_t offset) {
    void* mapData;
    memory->map(&mapData, size, offset);
    memcpy(mapData, data, size);
    memory->unmap();
}

void GpuBuffer::read(void* data, uint32_t size, uint32_t offset) {
    void* mapData;
    memory->map(&mapData, size, offset);
    memcpy(data, mapData, size);
    memory->unmap();
}

} // Vulkan

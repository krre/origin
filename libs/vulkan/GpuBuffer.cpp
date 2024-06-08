#include "GpuBuffer.h"
#include "api/buffer/Buffer.h"
#include "api/device/DeviceMemory.h"
#include "api/device/PhysicalDevice.h"
#include "api/command/CommandBufferOneTime.h"
#include "Renderer.h"
#include <cstring>

namespace Vulkan {

GpuBuffer::GpuBuffer(Device* device, VkBufferUsageFlagBits usage, uint32_t size) :
        m_usage(usage),
        m_size(size) {
    m_buffer = std::make_unique<Buffer>(device, usage, size);
    m_buffer->create();

    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(m_buffer->device()->handle(), m_buffer->handle(), &memRequirements);
    bool moveToDevice = false; // TODO: Pass to constructor
    VkMemoryPropertyFlags properties = !moveToDevice ?
                (VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT) :
                VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
    m_memory = std::make_unique<DeviceMemory>(device);
    m_memory->setMemoryTypeIndex(m_buffer->device()->physicalDevice()->findMemoryType(memRequirements.memoryTypeBits, properties));
    m_memory->allocate(memRequirements.size);

    vkBindBufferMemory(m_buffer->device()->handle(), m_buffer->handle(), m_memory->handle(), 0);
}

GpuBuffer::~GpuBuffer() {

}

VkBuffer GpuBuffer::handle() const {
    return m_buffer->handle();
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
    m_memory->map(&mapData, size, offset);
    memcpy(mapData, data, size);
    m_memory->unmap();
}

void GpuBuffer::read(void* data, uint32_t size, uint32_t offset) {
    void* mapData;
    m_memory->map(&mapData, size, offset);
    memcpy(data, mapData, size);
    m_memory->unmap();
}

}

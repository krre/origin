#include "VulkanGpuBuffer.h"
#include "Graphics/Vulkan/Wrapper/Buffer/Buffer.h"
#include "Graphics/Vulkan/Wrapper/Device/DeviceMemory.h"
#include "Graphics/Vulkan/Wrapper/Device/PhysicalDevice.h"
#include "Graphics/Vulkan/Wrapper/Command/CommandBufferOneTime.h"
#include "Graphics/Vulkan/VulkanRenderContext.h"


namespace Origin {

VulkanGpuBuffer::VulkanGpuBuffer(Usage usage, uint32_t size) : GpuBuffer(usage, size) {
    VkBufferUsageFlagBits usageFlagBits;
    if (usage == Usage::Vertex) {
        usageFlagBits = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
    } else if (usage == Usage::Index) {
        usageFlagBits = VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
    } else if (usage == Usage::Storage) {
        usageFlagBits == VK_BUFFER_USAGE_STORAGE_BUFFER_BIT;
    } else if (usage == Usage::Uniform) {
        usageFlagBits = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
    } else {
        std::runtime_error("Unknown usage type");
    }

    buffer = std::make_unique<Vulkan::Buffer>(vkCtx->getGraphicsDevice(), usageFlagBits, size);
    buffer->create();

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

VulkanGpuBuffer::~VulkanGpuBuffer() {

}

VkBuffer VulkanGpuBuffer::getHandle() const {
    return buffer->getHandle();
}

void VulkanGpuBuffer::copyToBuffer(Vulkan::Buffer* dstBuffer, VkDeviceSize size) {
    Vulkan::CommandBufferOneTime commandBuffer(buffer->getDevice(), vkCtx->getComputeCommandPool());

    VkBufferCopy bufferCopy = {};
    bufferCopy.size = size;
    commandBuffer.addBufferCopy(bufferCopy);
    commandBuffer.copyBuffer(buffer->getHandle(), dstBuffer->getHandle());

    commandBuffer.apply();
}

void VulkanGpuBuffer::write(const void* data, uint32_t size, uint32_t offset) {
    void* mapData;
    memory->map(&mapData, size, offset);
    memcpy(mapData, data, size);
    memory->unmap();
}

void VulkanGpuBuffer::read(void* data, uint32_t size, uint32_t offset) {
    void* mapData;
    memory->map(&mapData, size, offset);
    memcpy(data, mapData, size);
    memory->unmap();
}

} // Origin

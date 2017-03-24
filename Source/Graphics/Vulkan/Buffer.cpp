#include "Buffer.h"
#include "Manager.h"
#include "Queue/SubmitQueue.h"
#include "Command/CommandBuffers.h"
#include "Command/CommandBuffer.h"
#include <string.h>

using namespace Vulkan;

Buffer::Buffer(const Device* device, VkBufferUsageFlagBits usage, VkDeviceSize size, bool moveToDevice) :
        Devicer(device), memory(device), moveToDevice(moveToDevice) {
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
    CHECK_RESULT(vkCreateBuffer(device->getHandle(), &createInfo, nullptr, &handle), "Failed to create buffer");
    descriptorInfo.buffer = handle;
    descriptorInfo.offset = 0;
    descriptorInfo.range = createInfo.size;

    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(device->getHandle(), handle, &memRequirements);
    VkMemoryPropertyFlags properties = !moveToDevice ?
                (VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT) :
                VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
    memory.setMemoryTypeIndex(device->getPhysicalDevice()->findMemoryType(memRequirements.memoryTypeBits, properties));
    memory.allocate(memRequirements.size);

    vkBindBufferMemory(device->getHandle(), handle, memory.getHandle(), 0);
}

void Buffer::destroy() {
    VULKAN_DESTROY_HANDLE(vkDestroyBuffer(device->getHandle(), handle, nullptr))
}

void Buffer::write(VkDeviceSize offset, VkDeviceSize size, const void* data) {
    void* mapData;
    memory.map(size, offset, &mapData);
    memcpy(mapData, data, size);
    memory.unmap();
}

void Buffer::read(VkDeviceSize offset, VkDeviceSize size, void* data) {
    void* mapData;
    CHECK_RESULT(vkMapMemory(device->getHandle(), memory.getHandle(), offset, size, 0, &mapData), "Failed to map memory for reading");
    memcpy(data, mapData, size);
    vkUnmapMemory(device->getHandle(), memory.getHandle());
}

void Buffer::copyToBuffer(VkBuffer dstBuffer, VkDeviceSize size) {
    CommandBuffers commandBuffers(device, Manager::get()->getCommandPool());
    commandBuffers.allocate(1);

    CommandBuffer commandBuffer(commandBuffers.at(0));
    commandBuffer.begin(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);

    VkBufferCopy copyRegion = {};
    copyRegion.size = size;
    commandBuffer.addCopyRegion(copyRegion);
    commandBuffer.copyBuffer(handle, dstBuffer);

    commandBuffer.end();

    SubmitQueue queue(device, Manager::get()->getGraphicsFamily());
    queue.addCommandBuffer(commandBuffers.at(0));
    queue.submit();
    queue.waitIdle();
}

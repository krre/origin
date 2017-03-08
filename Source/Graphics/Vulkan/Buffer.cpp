#include "Buffer.h"
#include "Manager.h"
#include "Queue/SubmitQueue.h"
#include "Command/CommandBuffers.h"
#include "Command/CommandBuffer.h"
#include <string.h>

using namespace Vulkan;

Buffer::Buffer(const Device* device, VkBufferUsageFlagBits usage, VkDeviceSize size) :
    Devicer(device), memory(device) {
    createInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    createInfo.size = size;
    createInfo.usage = usage;
    createInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
}

Buffer::Buffer(const Device* device, VkDeviceSize size, Buffer::Type type, Buffer::Destination destination) :
    Devicer(device), memory(device), destination(destination) {
    createInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    createInfo.size = size;
    createInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    switch (type) {
    case Type::VERTEX:
        createInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
        break;
    case Type::INDEX:
        createInfo.usage = VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
        break;
    case Type::UNIFORM:
        createInfo.usage = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
        break;
    case Type::STORAGE:
        createInfo.usage = VK_BUFFER_USAGE_STORAGE_BUFFER_BIT;
        break;
    case Type::TRANSFER_SRC:
        createInfo.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
        break;
    case Type::TRANSFER_DST:
        createInfo.usage = VK_BUFFER_USAGE_TRANSFER_DST_BIT;
        break;
    default:
        break;
    }

    if (destination == Destination::DEVICE) {
        createInfo.usage |= VK_BUFFER_USAGE_TRANSFER_DST_BIT;
    }
}

Buffer::~Buffer() {
    destroy();
}

VkResult Buffer::create() {
    CHECK_RESULT(vkCreateBuffer(device->getHandle(), &createInfo, nullptr, &handle), "Failed to create buffer");
    descriptorInfo.buffer = handle;
    descriptorInfo.offset = 0;
    descriptorInfo.range = createInfo.size;

    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(device->getHandle(), handle, &memRequirements);
    VkMemoryPropertyFlags properties = destination == Destination::HOST ?
                (VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT) :
                VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
    memory.setMemoryTypeIndex(device->getPhysicalDevice()->findMemoryType(memRequirements.memoryTypeBits, properties));
    memory.allocate(memRequirements.size);

    vkBindBufferMemory(device->getHandle(), handle, memory.getHandle(), 0);

    return result;
}

void Buffer::destroy() {
    VULKAN_DESTROY_HANDLE(vkDestroyBuffer(device->getHandle(), handle, nullptr))
}

void Buffer::write(VkDeviceSize offset, VkDeviceSize size, const void* data) {
    void* mapData;
    CHECK_RESULT(vkMapMemory(device->getHandle(), memory.getHandle(), offset, size, 0, &mapData), "Failed to map memory for writing");
    memcpy(mapData, data, size);
    vkUnmapMemory(device->getHandle(), memory.getHandle());
}

void Buffer::read(VkDeviceSize offset, VkDeviceSize size, void* data) {
    void* mapData;
    CHECK_RESULT(vkMapMemory(device->getHandle(), memory.getHandle(), offset, size, 0, &mapData), "Failed to map memory for reading");
    memcpy(data, mapData, size);
    vkUnmapMemory(device->getHandle(), memory.getHandle());
}

void Buffer::copy(VkBuffer dstBuffer, VkDeviceSize size) {
    CommandBuffers commandBuffers(device, Manager::get()->getCommandPool());
    commandBuffers.allocate(1);

    CommandBuffer commandBuffer(commandBuffers.at(0));
    commandBuffer.begin(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);

    VkBufferCopy copyRegion = {};
    copyRegion.size = size;
    vkCmdCopyBuffer(commandBuffer.getHandle(), handle, dstBuffer, 1, &copyRegion);

    commandBuffer.end();

    SubmitQueue queue(device, Manager::get()->getGraphicsFamily());
    queue.addCommandBuffer(commandBuffers.at(0));
    queue.submit();
    queue.waitIdle();
}

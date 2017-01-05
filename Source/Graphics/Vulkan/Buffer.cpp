#include "Buffer.h"
#include "Manager.h"
#include "Queue/SubmitQueue.h"
#include "Command/CommandBuffers.h"
#include "Command/CommandBuffer.h"
#include <string.h>

using namespace Vulkan;

Buffer::Buffer(const Device* device, VkBufferUsageFlagBits usage, VkDeviceSize size) :
    device(device), memory(device) {
    createInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    createInfo.size = size;
    createInfo.usage = usage;
    createInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
}

Buffer::Buffer(const Device* device, VkDeviceSize size, Buffer::Type type, Buffer::Destination destination) :
    device(device), memory(device), destination(destination) {
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
}

Buffer::~Buffer() {
    if (handle != VK_NULL_HANDLE) {
        vkDestroyBuffer(device->getHandle(), handle, nullptr);
    }
}

VkResult Buffer::create() {
    VkResult result = checkError(vkCreateBuffer(device->getHandle(), &createInfo, nullptr, &handle), "Failed to create buffer");
    descriptorInfo.buffer = handle;
    descriptorInfo.offset = 0;
    descriptorInfo.range = createInfo.size;

    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(device->getHandle(), handle, &memRequirements);
    memory.setMemoryTypeIndex(Vulkan::Manager::get()->getPhysicalDevices()->findMemoryType(device->getPhysicalDevice(), memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT));
    memory.allocate(memRequirements.size);

    vkBindBufferMemory(device->getHandle(), handle, memory.getHandle(), 0);

    return result;
}

void Buffer::write(VkDeviceSize offset, VkDeviceSize size, const void* data) {
    void* mapData;
    vkMapMemory(device->getHandle(), memory.getHandle(), offset, size, 0, &mapData);
    memcpy(mapData, data, size);
    vkUnmapMemory(device->getHandle(), memory.getHandle());
}

void Buffer::read(VkDeviceSize offset, VkDeviceSize size, void* data) {
    void* mapData;
    vkMapMemory(device->getHandle(), memory.getHandle(), offset, size, 0, &mapData);
    memcpy(data, mapData, size);
    vkUnmapMemory(device->getHandle(), memory.getHandle());
}

void Buffer::copy(VkBuffer dstBuffer, VkDeviceSize size) {
    CommandBuffers commandBuffers(device, Manager::get()->getCommandPool());
    commandBuffers.allocate(1);

    CommandBuffer commandBuffer(commandBuffers.at(0));
    commandBuffer.setFlags(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);

    commandBuffer.begin();

    VkBufferCopy copyRegion = {};
    copyRegion.size = size;
    vkCmdCopyBuffer(commandBuffer.getHandle(), handle, dstBuffer, 1, &copyRegion);

    commandBuffer.end();

    SubmitQueue queue(device, Manager::get()->getGraphicsFamily());
    queue.setCommandBuffers({ commandBuffers.at(0) });
    queue.submit();
    queue.waitIdle();
}

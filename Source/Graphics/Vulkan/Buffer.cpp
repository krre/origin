#include "Buffer.h"

using namespace Vulkan;

Buffer::Buffer(const Device* device) : device(device) {
    createInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    createInfo.pNext = nullptr;
    createInfo.flags = 0;
    createInfo.size = 0;
    createInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
    createInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    createInfo.queueFamilyIndexCount = 0;
    createInfo.pQueueFamilyIndices = nullptr;
}

Buffer::~Buffer() {
    vkDestroyBuffer(device->getHandle(), handle, nullptr);
}

VkResult Buffer::create() {
    return checkError(vkCreateBuffer(device->getHandle(), &createInfo, nullptr, &handle), "Failed to create buffer");
}

void Buffer::setSize(VkDeviceSize size) {
    createInfo.size = size;
}

void Buffer::setUsage(VkBufferUsageFlags usage) {
    createInfo.usage = usage;
}

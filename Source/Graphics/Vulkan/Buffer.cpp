#include "Buffer.h"

using namespace Vulkan;

Buffer::Buffer(const Device* device, VkBufferUsageFlagBits usage) : device(device) {
    createInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    createInfo.size = 0;
    createInfo.usage = usage;
    createInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    createInfo.queueFamilyIndexCount = 0;
}

Buffer::~Buffer() {
    if (handle != VK_NULL_HANDLE) {
        vkDestroyBuffer(device->getHandle(), handle, nullptr);
    }
}

VkResult Buffer::create() {
    return checkError(vkCreateBuffer(device->getHandle(), &createInfo, nullptr, &handle), "Failed to create buffer");
}

void Buffer::setSize(VkDeviceSize size) {
    createInfo.size = size;
}

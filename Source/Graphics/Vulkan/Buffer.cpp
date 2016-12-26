#include "Buffer.h"

using namespace Vulkan;

Buffer::Buffer(const Device* device, VkBufferUsageFlagBits usage, VkDeviceSize size) : device(device) {
    createInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    createInfo.size = size;
    createInfo.usage = usage;
    createInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
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

    return result;
}

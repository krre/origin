#include "Buffer.h"

namespace Vulkan {

Buffer::Buffer(Device* device, VkBufferUsageFlagBits usage, VkDeviceSize size) :
        Devicer(device) {
    createInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    createInfo.size = size;
    createInfo.usage = usage;
    createInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
}

Buffer::~Buffer() {
    destroy();
}

void Buffer::create() {
    VULKAN_CHECK_RESULT(vkCreateBuffer(device->getHandle(), &createInfo, nullptr, &handle), "Failed to create buffer");
    descriptorInfo.buffer = handle;
    if (!descriptorInfo.range) {
        descriptorInfo.range = createInfo.size;
    }
}

void Buffer::destroy() {
    VULKAN_DESTROY_HANDLE(vkDestroyBuffer(device->getHandle(), handle, nullptr))
}

} // Vulkan

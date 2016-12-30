#include "Buffer.h"
#include "Manager.h"
#include <string.h>

using namespace Vulkan;

Buffer::Buffer(const Device* device, VkBufferUsageFlagBits usage, VkDeviceSize size) :
    device(device), memory(device) {
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

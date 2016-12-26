#include "MemoryBuffer.h"
#include "Manager.h"
#include <string.h>

using namespace Vulkan;

MemoryBuffer::MemoryBuffer(const Device* device, VkBufferUsageFlagBits usage, size_t size, const void* data) :
    device(device), buffer(device, usage), memory(device), data(data) {

    buffer.setSize(size);
    buffer.create();

    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(device->getHandle(), buffer.getHandle(), &memRequirements);
    memory.setAllocationSize(memRequirements.size);
    memory.setMemoryTypeIndex(Vulkan::Manager::get()->getPhysicalDevices()->findMemoryType(device->getPhysicalDevice(), memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT));
    memory.allocate();

    vkBindBufferMemory(device->getHandle(), buffer.getHandle(), memory.getHandle(), 0);
}

MemoryBuffer::~MemoryBuffer() {

}

void MemoryBuffer::update() {
    void* mapData;
    vkMapMemory(device->getHandle(), memory.getHandle(), 0, buffer.getSize(), 0, &mapData);
    memcpy(mapData, data, buffer.getSize());
    vkUnmapMemory(device->getHandle(), memory.getHandle());
}

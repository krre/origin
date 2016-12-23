#include "MemoryBuffer.h"

using namespace Vulkan;

MemoryBuffer::MemoryBuffer(const Device* device, VkBufferUsageFlagBits usage) :
    device(device), buffer(device, usage), memory(device) {

}

MemoryBuffer::~MemoryBuffer() {

}

void MemoryBuffer::setSize(VkDeviceSize size) {
    buffer.setSize(size);
}

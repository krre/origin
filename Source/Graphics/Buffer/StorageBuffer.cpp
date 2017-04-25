#include "StorageBuffer.h"
#include "Graphics/Vulkan/Buffer.h"

StorageBuffer::StorageBuffer(uint64_t size) {
    buffer = std::unique_ptr<Vulkan::Buffer>(new Vulkan::Buffer(VK_BUFFER_USAGE_STORAGE_BUFFER_BIT, size, false));
    buffer->create();
}

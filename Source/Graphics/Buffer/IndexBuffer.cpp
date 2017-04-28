#include "IndexBuffer.h"
#include "Graphics/Vulkan/Buffer.h"

IndexBuffer::IndexBuffer(uint64_t count) {
    VkDeviceSize size = count * (indexType == VK_INDEX_TYPE_UINT16 ? sizeof(uint16_t) : sizeof(uint32_t));
    buffer = std::unique_ptr<Vulkan::Buffer>(new Vulkan::Buffer(VK_BUFFER_USAGE_INDEX_BUFFER_BIT, size, false));
    buffer->create();
}

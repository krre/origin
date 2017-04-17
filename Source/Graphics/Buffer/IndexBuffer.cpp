#include "IndexBuffer.h"
#include "../Vulkan/Buffer.h"

IndexBuffer::IndexBuffer(uint64_t count, IndexBuffer::Type type) : type(type) {
    VkDeviceSize size = count * (type == Type::UINT16 ? sizeof(uint16_t) : sizeof(uint32_t));
    buffer = std::unique_ptr<Vulkan::Buffer>(new Vulkan::Buffer(VK_BUFFER_USAGE_INDEX_BUFFER_BIT, size, false));
    buffer->create();
}

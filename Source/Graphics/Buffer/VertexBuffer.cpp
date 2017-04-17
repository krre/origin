#include "VertexBuffer.h"
#include "../Vulkan/Buffer.h"

VertexBuffer::VertexBuffer(uint64_t size) {
    buffer = std::unique_ptr<Vulkan::Buffer>(new Vulkan::Buffer(VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, size, false));
    buffer->create();
}

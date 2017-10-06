#include "VertexBuffer.h"
#include "Graphics/Vulkan/Wrapper/Buffer/Buffer.h"

VertexBuffer::VertexBuffer(uint64_t size) {
    buffer = std::make_unique<Vulkan::Buffer>(VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, size, false);
    buffer->create();
}

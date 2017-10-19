#include "VertexBuffer.h"
#include "Graphics/Vulkan/Buffer/Buffer.h"
#include "Graphics/Vulkan/VulkanCore.h"

VertexBuffer::VertexBuffer(uint64_t size) {
    buffer = std::make_unique<Vulkan::Buffer>(VulkanCore::get()->getGraphicsDevice(), VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, size, false);
    buffer->create();
}

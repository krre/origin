#include "VertexBuffer.h"
#include "Graphics/Vulkan/Wrapper/Buffer/Buffer.h"
#include "Graphics/Vulkan/VulkanContext.h"

namespace Origin {

VertexBuffer::VertexBuffer(uint64_t size) {
    buffer = std::make_unique<Vulkan::Buffer>(static_cast<VulkanContext*>(VulkanContext::get())->getGraphicsDevice(), VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, size);
    buffer->create();
}

} // Origin

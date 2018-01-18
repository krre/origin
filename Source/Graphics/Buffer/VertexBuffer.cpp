#include "VertexBuffer.h"
#include "Graphics/Vulkan/Buffer/Buffer.h"
#include "Graphics/Render/RenderEngine.h"

namespace Origin {

VertexBuffer::VertexBuffer(uint64_t size) {
    buffer = std::make_unique<Vulkan::Buffer>(RenderEngine::get()->getGraphicsDevice(), VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, size);
    buffer->create();
}

} // Origin

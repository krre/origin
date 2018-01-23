#include "UniformBuffer.h"
#include "Vulkan/Buffer/Buffer.h"
#include "Graphics/Render/RenderEngine.h"

namespace Origin {

UniformBuffer::UniformBuffer(uint64_t size) {
    buffer = std::make_unique<Vulkan::Buffer>(RenderEngine::get()->getGraphicsDevice(), VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, size);
    buffer->create();
}

} // Origin

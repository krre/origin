#include "IndexBuffer.h"
#include "Graphics/Vulkan/Buffer/Buffer.h"
#include "Graphics/Render/RenderEngine.h"

namespace Origin {

IndexBuffer::IndexBuffer(uint64_t count) {
    VkDeviceSize size = count * (indexType == VK_INDEX_TYPE_UINT16 ? sizeof(uint16_t) : sizeof(uint32_t));
    buffer = std::make_unique<Vulkan::Buffer>(RenderEngine::get()->getGraphicsDevice(), VK_BUFFER_USAGE_INDEX_BUFFER_BIT, size);
    buffer->create();
}

} // Origin

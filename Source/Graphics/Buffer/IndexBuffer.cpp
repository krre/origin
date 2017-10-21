#include "IndexBuffer.h"
#include "Graphics/Vulkan/Buffer/Buffer.h"
#include "Graphics/Vulkan/Context.h"

IndexBuffer::IndexBuffer(uint64_t count) {
    VkDeviceSize size = count * (indexType == VK_INDEX_TYPE_UINT16 ? sizeof(uint16_t) : sizeof(uint32_t));
    buffer = std::make_unique<Vulkan::Buffer>(Vulkan::Context::get()->getGraphicsDevice(), VK_BUFFER_USAGE_INDEX_BUFFER_BIT, size, false);
    buffer->create();
}

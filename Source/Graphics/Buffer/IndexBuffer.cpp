#include "IndexBuffer.h"
#include "Graphics/Vulkan/Wrapper/Buffer/Buffer.h"
#include "Graphics/Vulkan/VulkanContext.h"

IndexBuffer::IndexBuffer(uint64_t count) {
    VkDeviceSize size = count * (indexType == VK_INDEX_TYPE_UINT16 ? sizeof(uint16_t) : sizeof(uint32_t));
    buffer = std::make_unique<Vulkan::Buffer>(static_cast<VulkanContext*>(VulkanContext::get())->getGraphicsDevice(), VK_BUFFER_USAGE_INDEX_BUFFER_BIT, size);
    buffer->create();
}

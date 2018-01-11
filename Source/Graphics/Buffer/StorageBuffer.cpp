#include "StorageBuffer.h"
#include "Graphics/Vulkan/Wrapper/Buffer/Buffer.h"
#include "Graphics/Vulkan/VulkanRenderContext.h"

namespace Origin {

StorageBuffer::StorageBuffer(uint64_t size) {
    buffer = std::make_unique<Vulkan::Buffer>(static_cast<VulkanRenderContext*>(VulkanRenderContext::get())->getGraphicsDevice(), VK_BUFFER_USAGE_STORAGE_BUFFER_BIT, size);
    buffer->create();
}

} // Origin

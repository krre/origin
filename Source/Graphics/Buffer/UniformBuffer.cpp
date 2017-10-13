#include "UniformBuffer.h"
#include "Graphics/Vulkan/Wrapper/Buffer/Buffer.h"
#include "Graphics/Vulkan/VulkanCore.h"

UniformBuffer::UniformBuffer(uint64_t size) {
    buffer = std::make_unique<Vulkan::Buffer>(VulkanCore::get()->getGraphicsDevice(), VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, size, false);
    buffer->create();
}

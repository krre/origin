#include "UniformBuffer.h"
#include "Graphics/Vulkan/Buffer/Buffer.h"

UniformBuffer::UniformBuffer(uint64_t size) {
    buffer = std::make_unique<Vulkan::Buffer>(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, size, false);
    buffer->create();
}

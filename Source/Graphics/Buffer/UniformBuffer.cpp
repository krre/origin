#include "UniformBuffer.h"
#include "Graphics/Vulkan/Buffer.h"

UniformBuffer::UniformBuffer(uint64_t size) {
    buffer = std::unique_ptr<Vulkan::Buffer>(new Vulkan::Buffer(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, size, false));
    buffer->create();
}

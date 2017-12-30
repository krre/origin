#include "UniformBuffer.h"
#include "Graphics/Vulkan/Wrapper/Buffer/Buffer.h"
#include "Graphics/Vulkan/Context.h"

UniformBuffer::UniformBuffer(uint64_t size) {
    buffer = std::make_unique<Vulkan::Buffer>(Vulkan::Context::get()->getGraphicsDevice(), VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, size);
    buffer->create();
}

#pragma once
#include "../../Core/Object.h"
#include "MemoryBuffer.h"

namespace Vulkan {

class Uniform : public Object {

public:
    Uniform(const Device* device, VkShaderStageFlags stage, uint32_t binding, size_t size, const void* data);
    void update();
    Buffer* getBuffer() { return memoryBuffer.getBuffer(); }
    VkDescriptorSetLayoutBinding* getDescriptorSetLayoutBinding() { return &layoutBinging; }

private:
    MemoryBuffer memoryBuffer;
    const void* data;
    VkDescriptorSetLayoutBinding layoutBinging = {};
};

} // Vulkan

#pragma once
#include "../../../Core/Object.h"
#include "../Buffer.h"
#include "../Image/Image.h"

namespace Vulkan {

class Descriptor : public Object {

public:
    Descriptor(const Device* device, VkShaderStageFlags stage, VkBufferUsageFlagBits usage, VkDescriptorType descriptorType, uint32_t binding, size_t size);
    ~Descriptor();
    void write(VkDeviceSize offset, VkDeviceSize size, const void* data);
    void read(VkDeviceSize offset, VkDeviceSize size, void* data);
    Buffer* getBuffer() { return &buffer; }
    Image* getImage() { return image; }
    VkDescriptorSetLayoutBinding* getLayoutBinding() { return &layoutBinging; }

private:
    Buffer buffer;
    Image* image = nullptr;
    VkDescriptorSetLayoutBinding layoutBinging = {};
};

} // Vulkan

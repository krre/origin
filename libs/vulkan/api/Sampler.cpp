#include "Sampler.h"

namespace Vulkan {

Sampler::Sampler(Device* device) : Devicer(device) {
    createInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
    createInfo.magFilter = VK_FILTER_NEAREST;
    createInfo.minFilter = VK_FILTER_NEAREST;
    createInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
    createInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    createInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    createInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    createInfo.mipLodBias = 0.0f;
    createInfo.compareOp = VK_COMPARE_OP_NEVER;
    createInfo.minLod = 0.0f;
    createInfo.maxLod = 1.0f;
    createInfo.maxAnisotropy = 1.0;
    createInfo.borderColor = VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE;
}

Sampler::~Sampler() {
    destroy();
}

void Sampler::create() {
    VULKAN_CHECK_RESULT(vkCreateSampler(device->getHandle(), &createInfo, nullptr, &handle), "Failed to create sampler");
}

void Sampler::destroy() {
    VULKAN_DESTROY_HANDLE(vkDestroySampler(device->getHandle(), handle, nullptr))
}

}

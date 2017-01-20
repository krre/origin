#include "Sampler.h"

using namespace Vulkan;

Sampler::Sampler(const Device* device) : device(device) {
    createInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
}

Sampler::~Sampler() {
    vkDestroySampler(device->getHandle(), handle, nullptr);
}

VkResult Sampler::create() {
    return checkError(vkCreateSampler(device->getHandle(), &createInfo, nullptr, &handle), "Failed to create sampler");
}

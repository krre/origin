#include "PipelineCache.h"

using namespace Vulkan;

PipelineCache::PipelineCache(const Device* device) : Devicer(device) {
    createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO;
}

PipelineCache::~PipelineCache() {
    destroy();
}

VkResult PipelineCache::create() {
    return checkError(vkCreatePipelineCache(device->getHandle(), &createInfo, nullptr, &handle), "Failed to create pipeline cache");
}

void PipelineCache::destroy() {
    VULKAN_DESTROY_HANDLE(vkDestroyPipelineCache(device->getHandle(), handle, nullptr))
}

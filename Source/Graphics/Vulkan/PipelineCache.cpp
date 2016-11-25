#include "PipelineCache.h"

using namespace Vulkan;

PipelineCache::PipelineCache(const Device* device) : device(device) {
    VkPipelineCacheCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO;
    result = vkCreatePipelineCache(device->getHandle(), &createInfo, nullptr, &handle);
}

PipelineCache::~PipelineCache() {
    if (handle != VK_NULL_HANDLE) {
        vkDestroyPipelineCache(device->getHandle(), handle, nullptr);
    }
}

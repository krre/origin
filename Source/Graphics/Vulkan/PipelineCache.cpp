#include "PipelineCache.h"

using namespace Vulkan;

PipelineCache::PipelineCache(const Device* device) : device(device) {
    createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO;
}

PipelineCache::~PipelineCache() {
    vkDestroyPipelineCache(device->getHandle(), handle, nullptr);
}

void PipelineCache::create() {
    checkError(vkCreatePipelineCache(device->getHandle(), &createInfo, nullptr, &handle));
}

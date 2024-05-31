#include "PipelineCache.h"

namespace Vulkan {

PipelineCache::PipelineCache(Device* device) : Devicer(device) {
    createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO;
}

PipelineCache::~PipelineCache() {
    destroy();
}

void PipelineCache::create() {
    VULKAN_CHECK_RESULT(vkCreatePipelineCache(device->getHandle(), &createInfo, nullptr, &handle), "Failed to create pipeline cache");
}

void PipelineCache::destroy() {
    VULKAN_DESTROY_HANDLE(vkDestroyPipelineCache(device->getHandle(), handle, nullptr))
}

}

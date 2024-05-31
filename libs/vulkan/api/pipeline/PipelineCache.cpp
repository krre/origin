#include "PipelineCache.h"

namespace Vulkan {

PipelineCache::PipelineCache(Device* device) : Devicer(device) {
    createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO;
}

PipelineCache::~PipelineCache() {
    destroy();
}

void PipelineCache::create() {
    VULKAN_CHECK_RESULT(vkCreatePipelineCache(m_device->handle(), &createInfo, nullptr, &m_handle), "Failed to create pipeline cache");
}

void PipelineCache::destroy() {
    VULKAN_DESTROY_HANDLE(vkDestroyPipelineCache(m_device->handle(), m_handle, nullptr))
}

}

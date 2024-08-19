#include "PipelineCache.h"

namespace Vulkan {

PipelineCache::PipelineCache(Device* device) : Devicer(device) {
    m_createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO;
}

PipelineCache::~PipelineCache() {
    vkDestroyPipelineCache(m_device->handle(), m_handle, nullptr);
}

void PipelineCache::create() {
    VULKAN_CHECK_RESULT(vkCreatePipelineCache(m_device->handle(), &m_createInfo, nullptr, &m_handle), "Failed to create pipeline cache");
}

}

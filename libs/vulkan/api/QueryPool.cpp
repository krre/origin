#include "QueryPool.h"

namespace Vulkan {

QueryPool::QueryPool(Device* device) : Devicer(device) {
    m_createInfo.sType = VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO;
    m_createInfo.queryType = VK_QUERY_TYPE_PIPELINE_STATISTICS;
}

QueryPool::~QueryPool() {
    vkDestroyQueryPool(m_device->handle(), m_handle, nullptr);
}

void QueryPool::create() {
    VULKAN_CHECK_RESULT(vkCreateQueryPool(m_device->handle(), &m_createInfo, nullptr, &m_handle), "Failed to create query pool");
}

}

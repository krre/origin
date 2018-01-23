#include "QueryPool.h"

namespace Origin {

namespace Vulkan {

QueryPool::QueryPool(Device* device) : Devicer(device) {
    createInfo.sType = VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO;
    createInfo.queryType = VK_QUERY_TYPE_PIPELINE_STATISTICS;
}

QueryPool::~QueryPool() {
    destroy();
}

void QueryPool::create() {
    VULKAN_CHECK_RESULT(vkCreateQueryPool(device->getHandle(), &createInfo, nullptr, &handle), "Failed to create query pool");
}

void QueryPool::destroy() {
    VULKAN_DESTROY_HANDLE(vkDestroyQueryPool(device->getHandle(), handle, nullptr))
}

} // Vulkan

} // Origin

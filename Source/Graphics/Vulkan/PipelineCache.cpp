#include "PipelineCache.h"

using namespace Vulkan;

PipelineCache::PipelineCache(const Device* device) : device(device) {

}

PipelineCache::~PipelineCache() {
    if (handle != VK_NULL_HANDLE) {
        vkDestroyPipelineCache(device->getHandle(), handle, nullptr);
    }
}

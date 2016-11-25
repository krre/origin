#include "Pipeline.h"

using namespace Vulkan;

Pipeline::Pipeline(const Device* device) : device(device) {

}

Pipeline::~Pipeline() {
    if (handle != VK_NULL_HANDLE) {
        vkDestroyPipeline(device->getHandle(), handle, nullptr);
    }
}

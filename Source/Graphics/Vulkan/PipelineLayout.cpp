#include "PipelineLayout.h"

using namespace Vulkan;

PipelineLayout::PipelineLayout(const Device* device) : device(device) {

}

PipelineLayout::~PipelineLayout() {
    if (handle != VK_NULL_HANDLE) {
        vkDestroyPipelineLayout(device->getHandle(), handle, nullptr);
    }
}

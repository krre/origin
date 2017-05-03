#include "BufferView.h"

using namespace Vulkan;

BufferView::BufferView(VkBuffer buffer, Device* device) :
        Devicer(device) {
    createInfo.sType = VK_STRUCTURE_TYPE_BUFFER_VIEW_CREATE_INFO;
    createInfo.buffer = buffer;
}

BufferView::~BufferView() {
    destroy();
}

void BufferView::create() {
    VULKAN_CHECK_RESULT(vkCreateBufferView(device->getHandle(), &createInfo, nullptr, &handle), "Failed to create buffer view");
}

void BufferView::destroy() {
    VULKAN_DESTROY_HANDLE(vkDestroyBufferView(device->getHandle(), handle, nullptr))
}
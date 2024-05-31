#include "BufferView.h"
#include "Buffer.h"

namespace Vulkan {

BufferView::BufferView(Device* device, Buffer* buffer) :
        Devicer(device) {
    createInfo.sType = VK_STRUCTURE_TYPE_BUFFER_VIEW_CREATE_INFO;
    createInfo.buffer = buffer->handle();
}

BufferView::~BufferView() {
    destroy();
}

void BufferView::create() {
    VULKAN_CHECK_RESULT(vkCreateBufferView(m_device->handle(), &createInfo, nullptr, &m_handle), "Failed to create buffer view");
}

void BufferView::destroy() {
    VULKAN_DESTROY_HANDLE(vkDestroyBufferView(m_device->handle(), m_handle, nullptr))
}

}

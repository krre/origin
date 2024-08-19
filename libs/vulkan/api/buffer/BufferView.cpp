#include "BufferView.h"
#include "Buffer.h"

namespace Vulkan {

BufferView::BufferView(Device* device, Buffer* buffer) :
        Devicer(device) {
    m_createInfo.sType = VK_STRUCTURE_TYPE_BUFFER_VIEW_CREATE_INFO;
    m_createInfo.buffer = buffer->handle();
}

BufferView::~BufferView() {
    vkDestroyBufferView(m_device->handle(), m_handle, nullptr);
}

void BufferView::create() {
    VULKAN_CHECK_RESULT(vkCreateBufferView(m_device->handle(), &m_createInfo, nullptr, &m_handle), "Failed to create buffer view");
}

}

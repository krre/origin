#include "Semaphore.h"

namespace Vulkan {

Semaphore::Semaphore(Device* device) : Devicer(device) {
    m_createInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
}

Semaphore::~Semaphore() {
    destroy();
}

void Semaphore::create() {
    VULKAN_CHECK_RESULT(vkCreateSemaphore(m_device->handle(), &m_createInfo, nullptr, &m_handle), "Failed to create semaphore");
}

void Semaphore::destroy() {
    VULKAN_DESTROY_HANDLE(vkDestroySemaphore(m_device->handle(), m_handle, nullptr))
}

}

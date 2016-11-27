#include "Semaphore.h"

using namespace Vulkan;

Semaphore::Semaphore(const Device* device) : device(device) {
    VkSemaphoreCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    result = vkCreateSemaphore(device->getHandle(), &createInfo, nullptr, &handle);
}

Semaphore::~Semaphore() {
    if (handle != VK_NULL_HANDLE) {
        vkDestroySemaphore(device->getHandle(), handle, nullptr);
    }
}

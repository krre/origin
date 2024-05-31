#include "Semaphore.h"

namespace Vulkan {

Semaphore::Semaphore(Device* device) : Devicer(device) {
    createInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
}

Semaphore::~Semaphore() {
    destroy();
}

void Semaphore::create() {
    VULKAN_CHECK_RESULT(vkCreateSemaphore(device->getHandle(), &createInfo, nullptr, &handle), "Failed to create semaphore");
}

void Semaphore::destroy() {
    VULKAN_DESTROY_HANDLE(vkDestroySemaphore(device->getHandle(), handle, nullptr))
}

}

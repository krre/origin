#include "Semaphore.h"

using namespace Vulkan;

Semaphore::Semaphore(const Device* device) : Devicer(device) {
    createInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
}

Semaphore::~Semaphore() {
    destroy();
}

VkResult Semaphore::create() {
    CHECK_RESULT(vkCreateSemaphore(device->getHandle(), &createInfo, nullptr, &handle), "Failed to create semaphore");
}

void Semaphore::destroy() {
    VULKAN_DESTROY_HANDLE(vkDestroySemaphore(device->getHandle(), handle, nullptr))
}

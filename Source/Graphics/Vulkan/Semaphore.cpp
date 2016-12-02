#include "Semaphore.h"

using namespace Vulkan;

Semaphore::Semaphore(const Device* device) : device(device) {
    createInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
}

Semaphore::~Semaphore() {
    vkDestroySemaphore(device->getHandle(), handle, nullptr);
}

bool Semaphore::create() {
    return checkError(vkCreateSemaphore(device->getHandle(), &createInfo, nullptr, &handle));
}

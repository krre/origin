#include "Buffer.h"

using namespace Vulkan;

Buffer::Buffer(const Device* device) : device(device) {

}

Buffer::~Buffer() {
    vkDestroyBuffer(device->getHandle(), handle, nullptr);
}

void Buffer::create() {
    checkError(vkCreateBuffer(device->getHandle(), &createInfo, nullptr, &handle));
}

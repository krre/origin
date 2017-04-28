#include "HardwareBuffer.h"
#include "Graphics/Vulkan/Buffer/Buffer.h"

HardwareBuffer::HardwareBuffer() {

}

HardwareBuffer::~HardwareBuffer() {

}

VkBuffer HardwareBuffer::getHandle() const {
    return buffer->getHandle();
}

void HardwareBuffer::write(const void* data, uint64_t size, uint64_t offset) {
    buffer->write(data, size, offset);
}

void HardwareBuffer::read(void* data, uint64_t size, uint64_t offset) {
    buffer->read(data, size, offset);
}

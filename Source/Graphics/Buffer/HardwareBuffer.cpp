#include "HardwareBuffer.h"
#include "Graphics/Vulkan/Buffer.h"

HardwareBuffer::HardwareBuffer() {

}

HardwareBuffer::~HardwareBuffer() {

}

VkBuffer HardwareBuffer::getHandle() const {
    return buffer->getHandle();
}

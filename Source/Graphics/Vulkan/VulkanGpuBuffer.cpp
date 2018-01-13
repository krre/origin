#include "VulkanGpuBuffer.h"

namespace Origin {

VulkanGpuBuffer::VulkanGpuBuffer(Usage usage, uint32_t size) : GpuBuffer(usage, size) {

}

VulkanGpuBuffer::~VulkanGpuBuffer() {

}

void VulkanGpuBuffer::write(const void* data, uint32_t size, uint32_t offset) {

}

void VulkanGpuBuffer::read(const void* data, uint32_t size, uint32_t offset) {

}

} // Origin

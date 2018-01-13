#pragma once
#include "Graphics/GpuBuffer.h"

namespace Origin {

class VulkanGpuBuffer : public GpuBuffer {

public:
    VulkanGpuBuffer(Usage usage, uint32_t size);
    ~VulkanGpuBuffer();

    void write(const void* data, uint32_t size, uint32_t offset = 0) override;
    void read(const void* data, uint32_t size, uint32_t offset = 0) override;

protected:
    uint32_t size = 0;
};

} // Origin

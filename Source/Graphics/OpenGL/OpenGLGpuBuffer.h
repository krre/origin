#pragma once
#include "Graphics/GpuBuffer.h"

namespace Origin {

class OpenGLGpuBuffer : public GpuBuffer {

public:
    OpenGLGpuBuffer(Usage usage, uint32_t size);
    ~OpenGLGpuBuffer();

    void write(const void* data, uint32_t size, uint32_t offset = 0) override;
    void read(void* data, uint32_t size, uint32_t offset = 0) override;

protected:
    uint32_t size = 0;
};

} // Origin

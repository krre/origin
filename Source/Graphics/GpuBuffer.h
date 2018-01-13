#pragma once
#include "Core/Object.h"

namespace Origin {

class GpuBuffer : public Object {

public:
    GpuBuffer(uint32_t size);
    ~GpuBuffer();

    virtual void write(const void* data, uint32_t size, uint32_t offset = 0) = 0;
    virtual void read(const void* data, uint32_t size, uint32_t offset = 0) = 0;

protected:
    uint32_t size = 0;
};

} // Origin

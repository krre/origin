#pragma once
#include "Core/Object.h"

namespace Origin {

class GpuBuffer : public Object {

public:

    enum class Usage {
        Vertex,
        Index,
        Storage,
        Uniform
    };

    GpuBuffer(Usage usage, uint32_t size);
    ~GpuBuffer();
    Usage getUsage() const { return usage; }
    uint32_t getSize() const { return size; }

    virtual void write(const void* data, uint32_t size, uint32_t offset = 0) = 0;
    virtual void read(void* data, uint32_t size, uint32_t offset = 0) = 0;

protected:
    uint32_t size = 0;
    Usage usage;
};

} // Origin

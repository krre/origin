#include "GpuBuffer.h"

namespace Origin {

GpuBuffer::GpuBuffer(Usage usage, uint32_t size) :
        usage(usage),
        size(size) {

}

GpuBuffer::~GpuBuffer() {

}

} // Origin

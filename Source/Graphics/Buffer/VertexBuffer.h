#pragma once
#include "HardwareBuffer.h"

namespace Origin {

class VertexBuffer : public HardwareBuffer {

public:
    VertexBuffer(uint64_t size);
};

} // Origin

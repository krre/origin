#pragma once
#include "HardwareBuffer.h"

namespace Origin {

class UniformBuffer : public HardwareBuffer {

public:
    UniformBuffer(uint64_t size);
};

} // Origin

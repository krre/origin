#pragma once
#include "HardwareBuffer.h"

class UniformBuffer : public HardwareBuffer {

public:
    UniformBuffer(uint64_t size);
};

#pragma once
#include "HardwareBuffer.h"

namespace Origin {

class StorageBuffer : public HardwareBuffer {

public:
    StorageBuffer(uint64_t size);
};

} // Origin

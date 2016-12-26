#pragma once
#include "../../Core/Object.h"
#include "MemoryBuffer.h"

namespace Vulkan {

class Uniform : public Object {

public:
    Uniform(const Device* device);

private:
    MemoryBuffer memoryBuffer;
};

} // Vulkan

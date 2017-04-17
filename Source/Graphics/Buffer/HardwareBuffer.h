#pragma once
#include "../../Core/Object.h"

namespace Vulkan {
    class Buffer;
}

class HardwareBuffer : public Object {

public:
//    HardwareBuffer() = delete;

protected:
    std::shared_ptr<Vulkan::Buffer> buffer;

private:
    std::shared_ptr<Vulkan::Buffer> stageBuffer; // TODO: Use for staging
};

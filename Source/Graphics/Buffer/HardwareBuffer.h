#pragma once
#include "../../Core/Object.h"

namespace Vulkan {
    class Buffer;
}

class HardwareBuffer : public Object {

public:
    HardwareBuffer();
    ~HardwareBuffer();

protected:
    std::unique_ptr<Vulkan::Buffer> buffer;
    std::unique_ptr<Vulkan::Buffer> stageBuffer; // TODO: Use for staging

private:

};

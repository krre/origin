#pragma once
#include "Core/Object.h"

namespace Vulkan {
    class Device;
}

namespace Origin {

class RenderPassResource : public Object {

public:
    RenderPassResource(Vulkan::Device* device, Object* parent = nullptr);
    ~RenderPassResource();

private:
    Vulkan::Device* device = nullptr;
};

} // Origin

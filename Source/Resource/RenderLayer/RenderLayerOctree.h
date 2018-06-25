#pragma once
#include "RenderLayer.h"

namespace Origin {

class RenderLayerOctree : public RenderLayer {

public:
    RenderLayerOctree(Vulkan::Device* device, Object* parent = nullptr);
    ~RenderLayerOctree();

private:

};

} // Origin

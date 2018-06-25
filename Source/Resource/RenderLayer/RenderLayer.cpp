#include "RenderLayer.h"

namespace Origin {

RenderLayer::RenderLayer(Vulkan::Device* device, Object* parent) :
    device(device), Object(parent) {

}

RenderLayer::~RenderLayer() {

}

} // Origin

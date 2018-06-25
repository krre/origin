#include "RenderPassResource.h"

namespace Origin {

RenderPassResource::RenderPassResource(Vulkan::Device* device, Object* parent) :
    device(device), Object(parent) {

}

RenderPassResource::~RenderPassResource() {

}

} // Origin

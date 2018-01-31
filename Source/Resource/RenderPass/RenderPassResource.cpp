#include "RenderPassResource.h"
#include "VulkanRenderer/API/RenderPass.h"

namespace Origin {

RenderPassResource::RenderPassResource(Vulkan::Device* device) {
    renderPass = std::make_unique<Vulkan::RenderPass>(device);
}

RenderPassResource::~RenderPassResource() {

}

} // Origin

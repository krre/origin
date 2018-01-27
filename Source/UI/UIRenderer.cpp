#include "UIRenderer.h"
#include "VulkanRenderer/GpuBuffer.h"

namespace Origin {

UIRenderer::UIRenderer() {
    uint32_t startSize = 10000; // TODO: Set optimal value or take from constant
    vertexBuffer = std::make_unique<Vulkan::GpuBuffer>(VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, startSize);
}

UIRenderer::~UIRenderer() {

}

void UIRenderer::addBatch(Batch2D batch) {
    batches.push_back(batch);
}

} // Origin

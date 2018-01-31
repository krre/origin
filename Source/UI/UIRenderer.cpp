#include "UIRenderer.h"
#include "VulkanRenderer/GpuBuffer.h"
#include "Resource/RenderPass/RenderPassUI.h"
#include "Graphics/Render/RenderEngine.h"

namespace Origin {

UIRenderer::UIRenderer() {
    renderPassUI = std::make_unique<RenderPassUI>(RenderEngine::get()->getGraphicsDevice());

    uint32_t startSize = 10000; // TODO: Set optimal value or take from constant
    vertexBuffer = std::make_unique<Vulkan::GpuBuffer>(VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, startSize);
}

UIRenderer::~UIRenderer() {

}

void UIRenderer::addBatch(UIBatch batch) {
    batches.push_back(batch);
}

void UIRenderer::drawBatches() {
    uint32_t size = vertices.size() * sizeof(UIBatch::Vertex);

    if (size > vertexBuffer->getSize()) {
        vertexBuffer = std::make_unique<Vulkan::GpuBuffer>(VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, size);
    }

    if (size) {
        vertexBuffer->write(vertices.data(), size);
    }

    batches.clear();
    vertices.clear();
}

} // Origin

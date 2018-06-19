#include "UIRenderer.h"
#include "Vulkan/GpuBuffer.h"
#include "Resource/RenderPass/RenderPassUI.h"
#include "Graphics/Render/RenderManager.h"
#include "Base/Game.h"

namespace Origin {

UIRenderer::UIRenderer(Object* parent) : Object(parent) {
    renderPassUI = new RenderPassUI(RenderManager::get()->getGraphicsDevice(), this);
}

UIRenderer::~UIRenderer() {

}

void UIRenderer::addBatch(UIBatch batch) {
    batches.push_back(batch);
}

void UIRenderer::drawBatches() {
    renderPassUI->setVertexCount(vertices.size());

    uint32_t size = vertices.size() * sizeof(UIBatch::Vertex);

    if (size) {
        renderPassUI->getVertexBuffer()->write(vertices.data(), size);
        renderPassUI->setTexture(batches.at(0).texture); // TODO: Sort batches and swith textures
    }

    batches.clear();
    vertices.clear();
}

} // Origin

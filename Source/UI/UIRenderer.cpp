#include "UIRenderer.h"
#include "VulkanRenderer/GpuBuffer.h"
#include "Resource/RenderPass/RenderPassUI.h"
#include "Graphics/Render/RenderManager.h"
#include "Base/Game.h"

namespace Origin {

UIRenderer::UIRenderer(Object* parent) : Object(parent) {
    renderPassUI = new RenderPassUI(Game::getRenderManager()->getGraphicsDevice(), this);
}

UIRenderer::~UIRenderer() {

}

void UIRenderer::addBatch(UIBatch batch) {
    batches.push_back(batch);
}

void UIRenderer::drawBatches() {
    uint32_t size = vertices.size() * sizeof(UIBatch::Vertex);

    renderPassUI->setVertexCount(vertices.size());

    if (size > renderPassUI->getVertexBuffer()->getSize()) {
        renderPassUI->resizeVertexBuffer(size);
    }

    if (size) {
        renderPassUI->getVertexBuffer()->write(vertices.data(), size);
        renderPassUI->setTexture(batches.at(0).texture); // TODO: Sort batches and swith textures
    }

    batches.clear();
    vertices.clear();
}

} // Origin

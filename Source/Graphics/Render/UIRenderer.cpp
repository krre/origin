#include "UIRenderer.h"
#include "Vulkan/GpuBuffer.h"
#include "Resource/RenderPass/RenderPassUI.h"
#include "Graphics/Render/RenderManager.h"
#include "Base/Game.h"

namespace Origin {

UIRenderer::UIRenderer(Object* parent) : Renderer(parent) {
    renderPassUI = new RenderPassUI(RenderManager::get()->getGraphicsDevice(), this);
}

UIRenderer::~UIRenderer() {

}

void UIRenderer::render() {
    renderPassUI->setVertexCount(vertices.size());

    uint32_t size = vertices.size() * sizeof(UIBatch::Vertex);

    if (size) {
        renderPassUI->getVertexBuffer()->write(vertices.data(), size);
        renderPassUI->setTexture(batches.at(0).texture); // TODO: Sort batches and swith textures
    }

    batches.clear();
    vertices.clear();
}

RenderPassResource* UIRenderer::getRenderPass() const {
    return renderPassUI;
}

void UIRenderer::addBatch(UIBatch batch) {
    batches.push_back(batch);
}

} // Origin

#include "UIRenderer.h"
#include "Vulkan/GpuBuffer.h"
#include "Resource/RenderLayer/RenderLayerUI.h"
#include "Graphics/Render/RenderManager.h"

namespace Origin {

static UIRenderer* instance = nullptr;

UIRenderer::UIRenderer(Object* parent) : Renderer(parent) {
    instance = this;
    renderLayerUI = new RenderLayerUI(RenderManager::get()->getGraphicsDevice(), this);
}

UIRenderer::~UIRenderer() {

}

UIRenderer* UIRenderer::get() {
    return instance;
}

void UIRenderer::draw() {
    renderLayerUI->setVertexCount(vertices.size());

    uint32_t size = vertices.size() * sizeof(UIBatch::Vertex);

    if (size) {
        renderLayerUI->getVertexBuffer()->write(vertices.data(), size);
        renderLayerUI->setTexture(batches.at(0).texture); // TODO: Sort batches and swith textures
    }

    batches.clear();
    vertices.clear();
}

RenderLayer* UIRenderer::getRenderLayer() const {
    return renderLayerUI;
}

void UIRenderer::addBatch(UIBatch batch) {
    batches.push_back(batch);
}

} // Origin

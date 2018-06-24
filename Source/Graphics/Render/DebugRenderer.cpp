#include "DebugRenderer.h"

namespace Origin {

static DebugRenderer* instance = nullptr;

DebugRenderer::DebugRenderer(Object* parent) : Renderer(parent) {
    instance = this;
    setActive(false);
}

DebugRenderer::~DebugRenderer() {

}

DebugRenderer* DebugRenderer::get() {
    return instance;
}

void DebugRenderer::draw() {

}

RenderPassResource* DebugRenderer::getRenderPass() const {
    return nullptr;
}

} // Origin

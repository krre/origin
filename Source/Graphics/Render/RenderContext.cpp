#include "RenderContext.h"
#include "Core/Window.h"

namespace Origin {

RenderContext::RenderContext() {

}

RenderContext::~RenderContext() {

}

void RenderContext::init() {
    renderer = createRenderer();
}

void RenderContext::shutdown() {
    renderer.reset();
}

Renderer*RenderContext::getRenderer() const {
    return renderer.get();
}

} // Origin

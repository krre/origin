#include "RenderContext.h"
#include "Graphics/Render/RenderWindow.h"

namespace Origin {

RenderContext::RenderContext() {

}

RenderContext::~RenderContext() {

}

void RenderContext::init() {
    renderer = createRenderer();
}

Renderer*RenderContext::getRenderer() const {
    return renderer.get();
}

} // Origin

#include "GraphicsContext.h"
#include "Graphics/Render/RenderWindow.h"

GraphicsContext::GraphicsContext() {
}

GraphicsContext::~GraphicsContext() {
    if (renderWindow != nullptr) {
        delete renderWindow;

    }
}

RenderWindow* GraphicsContext::createRenderWindow() {
    assert(renderWindow == nullptr);
    renderWindow = createRenderWindowImpl();
}

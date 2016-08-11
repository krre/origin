#include "OctreeRenderer.h"
#include "RenderSurface.h"

OctreeRenderer::OctreeRenderer() {

}

void OctreeRenderer::render() {
    uint32_t* data = renderSurface->getData();
    int count = renderSurface->getWidth() * renderSurface->getHeight();
    for (int i = 0; i < count; i++) {
        if (i < 98000) {
            data[i] = 0x0000ffff;
        } else {
            data[i] = 0xff0000ff;
        }
    }
}

void OctreeRenderer::setRenderSurface(RenderSurface* renderSurface) {
    this->renderSurface = renderSurface;
}

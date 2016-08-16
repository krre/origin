#include "OctreeRenderer.h"
#include "RenderSurface.h"

OctreeRenderer::OctreeRenderer() {

}

void OctreeRenderer::render(const RenderSurface* renderSurface) {
    uint32* data = renderSurface->getData();
    int count = renderSurface->getWidth() * renderSurface->getHeight();
    for (int i = 0; i < count; i++) {
        if (i < 98000) {
            data[i] = 0x0000ffff;
        } else {
            data[i] = 0xff0000ff;
        }
    }
}

#include "Renderer.h"
#include "Core/Screen.h"
#include "Renderer2D.h"
#include "Renderer3D.h"
#include "Gui/Control.h"
#include "Gui/Batch2D.h"

namespace Origin {

Renderer::Renderer() {
    renderer2d = std::make_unique<Renderer2D>();
    renderer3d = std::make_unique<Renderer3D>();


}

Renderer::~Renderer() {

}

void Renderer::render(Screen* screen) {
    renderer2d->prepare(screen->getRootControl());
    renderer2d->render();

    for (auto view3d : renderer2d->getRenderViews()) {
        renderer3d->render(view3d);
    }

    renderQueue();
}

void Renderer::createRenderStates() {
    // Shape2D
    std::unique_ptr<RenderState> shape2DRS = std::make_unique<RenderState>();
    renderStates[RenderState::Type::Shape2D] = std::move(shape2DRS);

    // Freetype text
    std::unique_ptr<RenderState> freeTypeTextRS = std::make_unique<RenderState>();
    renderStates[RenderState::Type::FreeTypeText] = std::move(freeTypeTextRS);

    // SDF text
    std::unique_ptr<RenderState> sdfTextRS = std::make_unique<RenderState>();
    renderStates[RenderState::Type::SdfText] = std::move(sdfTextRS);

    // Voxel
    std::unique_ptr<RenderState> voxelRS = std::make_unique<RenderState>();
    renderStates[RenderState::Type::Voxel] = std::move(voxelRS);
}

} // Origin

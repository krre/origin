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

} // Origin

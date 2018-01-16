#include "Renderer.h"
#include "Core/Screen.h"
#include "Renderer2D.h"
#include "Gui/Control.h"
#include "Gui/Batch2D.h"

namespace Origin {

Renderer::Renderer() {
    renderer2d = std::make_unique<Renderer2D>();
}

Renderer::~Renderer() {

}

void Renderer::render(Screen* screen) {

    renderQueue();
}

} // Origin

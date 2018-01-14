#include "Renderer.h"
#include "Core/Screen.h"
#include "Gui/Control.h"
#include "Gui/Batch2D.h"

namespace Origin {

Renderer::Renderer() {

}

Renderer::~Renderer() {

}

void Renderer::render(Screen* screen) {

    renderQueue();
}

} // Origin

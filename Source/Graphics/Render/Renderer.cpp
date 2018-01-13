#include "Renderer.h"
#include "Core/Screen.h"
#include "UI/Control.h"
#include "UI/Batch2D.h"

namespace Origin {

Renderer::Renderer() {

}

Renderer::~Renderer() {

}

void Renderer::render(Screen* screen) {

    renderQueue();
}

} // Origin

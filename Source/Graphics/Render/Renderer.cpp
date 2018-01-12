#include "Renderer.h"

namespace Origin {

Renderer::Renderer() {

}

Renderer::~Renderer() {

}

void Renderer::render(Screen* screen) {
    renderQueue();
}

} // Origin

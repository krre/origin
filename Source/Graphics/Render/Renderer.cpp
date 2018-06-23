#include "Renderer.h"

namespace Origin {

Renderer::Renderer(Object* parent) : Object(parent) {

}

Renderer::~Renderer() {

}

void Renderer::setActive(bool active) {
    this->active = active;
}

} // Origin

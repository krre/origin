#include "Renderer.h"
#include <SDL_opengl.h>
#include <assert.h>

Renderer::Renderer() {

}

void Renderer::render(float dt) {
    assert(entities);
    for (auto entity : (*entities)) {

    }
}

void Renderer::setEntities(std::vector<Entity*>* entities) {
    this->entities = entities;
}

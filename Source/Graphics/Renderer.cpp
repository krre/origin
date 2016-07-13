#include "Renderer.h"
#include "../ECS/Components/Components.h"
#include <SDL_opengl.h>
#include <assert.h>

Renderer::Renderer() {

}

void Renderer::render(float dt) {
    assert(entities);
    for (auto entity : *entities) {
        RenderComponent* renderComp = static_cast<RenderComponent*>(entity->getComponent(ComponentType::Render));
        renderComp->drawable->draw(dt);
    }
}

void Renderer::setEntities(std::vector<Entity*>* entities) {
    this->entities = entities;
}

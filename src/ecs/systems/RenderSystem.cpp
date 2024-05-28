#include "RenderSystem.h"

RenderSystem::RenderSystem(EntityManager* entityManager) : System(entityManager) {
    type = System::Type::Render;
}

void RenderSystem::process(float dt) {

}

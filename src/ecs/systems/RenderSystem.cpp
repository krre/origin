#include "RenderSystem.h"

RenderSystem::RenderSystem(EntityManager* entityManager) : System(entityManager) {
    m_type = System::Type::Render;
}

void RenderSystem::process(float dt) {

}

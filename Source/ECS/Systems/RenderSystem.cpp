#include "RenderSystem.h"
#include "Graphics/Drawable.h"

namespace Origin {

RenderSystem::RenderSystem(EntityManager* entityManager) : System(entityManager) {
    type = System::Type::Render;
}

void RenderSystem::process(float dt) {
    for (const auto& drawable : drawables) {
        if (drawable->getVisible()) {
            drawable->draw(dt);
        }
    }
}

} // Origin

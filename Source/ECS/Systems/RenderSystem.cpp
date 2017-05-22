#include "RenderSystem.h"
#include "Graphics/Drawable.h"

RenderSystem::RenderSystem() {
    type = SystemType::Render;
}

void RenderSystem::process(float dt) {
    for (const auto& drawable : drawables) {
        if (drawable->getVisible()) {
            drawable->draw(dt);
        }
    }
}

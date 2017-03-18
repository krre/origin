#include "RenderSystem.h"

RenderSystem::RenderSystem() {
    type = SystemType::Render;
}

void RenderSystem::process(float dt) {
    for (auto& drawable : drawables) {
        if (drawable->getVisible()) {
            drawable->draw(dt);
        }
    }
}

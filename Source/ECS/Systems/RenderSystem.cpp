#include "RenderSystem.h"
#include "../../Debug/Console.h"
#include "../../Debug/DebugHUD.h"
#include "../../Core/App.h"
#include "../../UI/Toast.h"
#include "../../ECS/Engine.h"
#include "../../ECS/Components/Components.h"

RenderSystem::RenderSystem() {
    type = SystemType::Render;
    drawables.push_back(Toast::get());
}

void RenderSystem::process(float dt) {
    for (auto drawable : drawables) {
        if (drawable->getVisible()) {
            drawable->draw(dt);
        }
    }
}

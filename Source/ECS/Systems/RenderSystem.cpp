#include "RenderSystem.h"
#include "../../Debug/Console.h"
#include "../../Debug/DebugHUD.h"
#include "../Core/App.h"
#include "../UI/Toast.h"

RenderSystem::RenderSystem() {
    type = SystemType::Render;
    // Order important!
    // From bottom layer to top
    drawables.push_back(Console::getInstance());
    drawables.push_back(DebugHUD::getInstance());
    drawables.push_back(Toast::getInstance());
}

void RenderSystem::process(float dt) {
    renderer.render(dt);

    App::getInstance()->getViewport()->render();
    for (auto drawable : drawables) {
        if (drawable->getVisible()) {
            drawable->draw(dt);
        }
    }
}

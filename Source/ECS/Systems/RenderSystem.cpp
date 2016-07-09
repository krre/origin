#include "RenderSystem.h"
#include "../../Debug/Console.h"
#include "../Core/App.h"

RenderSystem::RenderSystem() {
    type = SystemType::Render;
}

void RenderSystem::process(float dt) {
    App::getInstance()->getViewport()->render();

    if (Console::getInstance()->getVisible()) {
        Console::getInstance()->render(dt);
    }
}

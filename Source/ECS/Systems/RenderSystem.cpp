#include "RenderSystem.h"
#include "../../Debug/Console.h"

RenderSystem::RenderSystem() {
    type = SystemType::Render;
}

void RenderSystem::process(float dt) {
    if (Console::getInstance()->getVisible()) {
        Console::getInstance()->render(dt);
    }
}

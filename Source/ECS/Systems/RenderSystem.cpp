#include "RenderSystem.h"
#include "../../Debug/Console.h"
#include "../../Debug/DebugHUD.h"
#include "../Core/App.h"
#include "../UI/Toast.h"

RenderSystem::RenderSystem() {
    type = SystemType::Render;
}

void RenderSystem::process(float dt) {
    App::getInstance()->getViewport()->render();

    if (Console::getInstance()->getVisible()) {
        Console::getInstance()->draw(dt);
    }

    if (DebugHUD::getInstance()->getVisible()) {
        DebugHUD::getInstance()->draw(dt);
    }

    if (Toast::getInstance()->getVisible()) {
        Toast::getInstance()->draw(dt);
    }
}

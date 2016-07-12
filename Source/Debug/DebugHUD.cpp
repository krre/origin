#include "DebugHUD.h"
#include "../Core/App.h"
#include <glm/glm.hpp>

DebugHUD::DebugHUD() {
    visible = false;
}

void DebugHUD::draw(float dt) {
    fpsText.setPosition(glm::vec2(10, App::getInstance()->getHeight() - 20));
    fpsText.setText("FPS: " + std::to_string(1.0 / dt));
    fpsText.draw(dt);
}

void DebugHUD::trigger() {
    visible = !visible;
}

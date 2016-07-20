#include "DebugHUD.h"
#include "../Core/App.h"
#include <glm/glm.hpp>

DebugHUD::DebugHUD() {
    visible = false;
}

void DebugHUD::draw(float dt) {
    fpsText.setPosition(glm::vec2(5, App::getInstance()->getHeight() - 20));
    accumTime += dt;
    counter++;
    if (accumTime >= 0.5) {
        // Average fps for 0.5 sec
        fpsText.setText(std::to_string(int(std::round(counter / accumTime))) + " fps");
        accumTime = 0;
        counter = 0;
    }
    fpsText.draw(dt);
}

void DebugHUD::trigger() {
    visible = !visible;
}

#include "DebugHUD.h"
#include "../Core/App.h"
#include <glm/glm.hpp>
#include <Gagarin.h>

DebugHUD::DebugHUD() {
    visible = false;
    version.setText("Gagarin " + std::string(VERSION_STRING));
}

void DebugHUD::draw(float dt) {
    version.setPosition(glm::vec2(5, App::getInstance()->getHeight() - 15));
    fpsText.setPosition(glm::vec2(5, App::getInstance()->getHeight() - 32));

    accumTime += dt;
    counter++;
    if (accumTime >= 0.5) {
        // Average fps for 0.5 sec
        fpsText.setText(std::to_string(int(std::round(counter / accumTime))) + " fps");
        accumTime = 0;
        counter = 0;
    }
    version.draw(dt);
    fpsText.draw(dt);
}

void DebugHUD::trigger() {
    visible = !visible;
}

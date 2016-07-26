#include "DebugHUD.h"
#include "../Core/App.h"
#include <glm/glm.hpp>
#include <Gagarin.h>

DebugHUD::DebugHUD() {
    visible = false;
    version.resize(100, 10);
    fps.resize(100, 10);

    version.setText("Gagarin " + std::string(VERSION_STRING));
    statisticsLayout->setPosition(glm::vec2(5, 5));
    statisticsLayout->addControl(&version);
    statisticsLayout->addControl(&fps);
    setLayout(statisticsLayout);
}

void DebugHUD::draw(float dt) {
//    version.setPosition(glm::vec2(5, App::getInstance()->getHeight() - 15));
//    fps.setPosition(glm::vec2(5, App::getInstance()->getHeight() - 32));

    accumTime += dt;
    counter++;
    if (accumTime >= 0.5) {
        // Average fps for 0.5 sec
        fps.setText(std::to_string(int(std::round(counter / accumTime))) + " fps");
        accumTime = 0;
        counter = 0;
    }
    Scene2D::draw(dt);
}

void DebugHUD::trigger() {
    visible = !visible;
}

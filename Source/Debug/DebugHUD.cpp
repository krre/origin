#include "DebugHUD.h"
#include "../Core/App.h"
#include <glm/glm.hpp>
#include <Gagarin.h>

DebugHUD::DebugHUD() {
    visible = false;
    version.resize(100, 10);
    fps.resize(100, 10);

    version.setText("Gagarin " + std::string(VERSION_STRING));
    statisticsLayout->setPosition(glm::vec2(5, 15));
    statisticsLayout->addControl(&version);
    statisticsLayout->addControl(&fps);
    setLayout(statisticsLayout);
}

void DebugHUD::draw(float dt) {
    accumTime += dt;
    counter++;
    if (accumTime >= 0.5) {
        // Average fps for 0.5 sec (on resize may be > 60, so clamp to 60)
        int fpsNumber = std::min(int(std::round(counter / accumTime)), 60);
        fps.setText(std::to_string(fpsNumber) + " fps");
        accumTime = 0;
        counter = 0;
    }
    Scene2D::draw(dt);
}

void DebugHUD::trigger() {
    visible = !visible;
}

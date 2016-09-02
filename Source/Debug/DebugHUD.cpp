#include "DebugHUD.h"
#include "../Core/App.h"
#include <glm/glm.hpp>
#include <Gagarin.h>

DebugHUD::DebugHUD() : Scene2D(500, 500) {
    visible = false;

    version.resize(100, 10);
    version.setZ(1.0f);
    version.setText("Gagarin " + std::string(VERSION_STRING));

    openGL.resize(100, 10);
    openGL.setZ(1.0);
    openGL.setText("OpenGL " + std::string(reinterpret_cast<const char*>(glGetString(GL_VERSION))));

    print(glGetString(GL_VERSION));

    fps.resize(100, 10);
    fps.setZ(1.0f);

    statisticsLayout->setPosition(glm::vec2(5, 15));
    statisticsLayout->addControl(&version);
    statisticsLayout->addControl(&openGL);
    statisticsLayout->addControl(&fps);
    setLayout(statisticsLayout);

    Event::getInstance()->windowResize.connect<DebugHUD, &DebugHUD::onWindowResize>(this);
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

void DebugHUD::onWindowResize(int width, int height) {
    resize(width, height);
}

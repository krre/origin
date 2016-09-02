#include "DebugHUD.h"
#include "../Core/App.h"
#include <glm/glm.hpp>
#include <Gagarin.h>

DebugHUD::DebugHUD() : Scene2D(500, 500) {
    visible = false;

    version.resize(100, 10);
    version.setZ(1.0f);
    version.setText("Gagarin " + std::string(VERSION_STRING));

    vendor.resize(100, 10);
    vendor.setZ(1.0);
    vendor.setText("Video driver: " + std::string(reinterpret_cast<const char*>(glGetString(GL_VENDOR))));

    openGL.resize(100, 10);
    openGL.setZ(1.0);
    openGL.setText("OpenGL " + std::string(reinterpret_cast<const char*>(glGetString(GL_VERSION))));

    cpuCount.resize(100, 10);
    cpuCount.setZ(1.0);
    cpuCount.setText("CPU count: " + std::to_string(SDL_GetCPUCount()));

    systemRAM.resize(100, 10);
    systemRAM.setZ(1.0);
    systemRAM.setText("System RAM: " + std::to_string(SDL_GetSystemRAM()) + " MB");

    arbSSBO.resize(100, 10);
    arbSSBO.setZ(1.0);
    arbSSBO.setText(std::string("GL_ARB_shader_storage_buffer_object: ") + (SDL_GL_ExtensionSupported("GL_ARB_shader_storage_buffer_object") ? "Yes" : "No"));

    arbCS.resize(100, 10);
    arbCS.setZ(1.0);
    arbCS.setText(std::string("GL_ARB_compute_shader: ") +  + (SDL_GL_ExtensionSupported("GL_ARB_compute_shader") ? "Yes" : "No"));

    fps.resize(100, 10);
    fps.setZ(1.0f);

    statisticsLayout->setPosition(glm::vec2(5, 15));
    statisticsLayout->addControl(&version);
    statisticsLayout->addControl(&vendor);
    statisticsLayout->addControl(&openGL);
    statisticsLayout->addControl(&cpuCount);
    statisticsLayout->addControl(&systemRAM);
    statisticsLayout->addControl(&arbSSBO);
    statisticsLayout->addControl(&arbCS);
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

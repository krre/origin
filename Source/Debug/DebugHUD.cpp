#include "DebugHUD.h"
#include "../Core/App.h"
#include "../Core/Game.h"
#include "../ECS/Engine.h"
#include "../ECS/Components/TransformComponent.h"
#include <glm/glm.hpp>
#include <Gagarin.h>

DebugHUD::DebugHUD() : Scene2D(500, 500) {
//    visible = false;

    version.resize(100, 10);
    version.setZ(1.0f);
    version.setText("Gagarin " + std::string(VERSION_STRING));

    vendor.resize(100, 10);
    vendor.setZ(1.0);
//    vendor.setText("Video driver: " + std::string(reinterpret_cast<const char*>(glGetString(GL_VENDOR))));

    openGL.resize(100, 10);
    openGL.setZ(1.0);
//    openGL.setText("OpenGL " + std::string(reinterpret_cast<const char*>(glGetString(GL_VERSION))));

    cpuCount.resize(100, 10);
    cpuCount.setZ(1.0);
    cpuCount.setText("CPU count: " + std::to_string(SDL_GetCPUCount()));

    systemRAM.resize(100, 10);
    systemRAM.setZ(1.0);
    systemRAM.setText("System RAM: " + std::to_string(SDL_GetSystemRAM()) + " MB");

    fps.resize(100, 10);
    fps.setZ(1.0f);

    posX.resize(100, 10);
    posX.setZ(1.0f);

    posY.resize(100, 10);
    posY.setZ(1.0f);

    posZ.resize(100, 10);
    posZ.setZ(1.0f);

    statisticsLayout->setPosition(glm::vec2(5, 15));
    statisticsLayout->addControl(&version);
    statisticsLayout->addControl(&vendor);
    statisticsLayout->addControl(&openGL);
    statisticsLayout->addControl(&cpuCount);
    statisticsLayout->addControl(&systemRAM);
    statisticsLayout->addControl(&fps);
    statisticsLayout->addControl(&posX);
    statisticsLayout->addControl(&posY);
    statisticsLayout->addControl(&posZ);
    setLayout(statisticsLayout);

    Event::get()->windowResize.connect<DebugHUD, &DebugHUD::onWindowResize>(this);
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
    Entity* character = Engine::get()->getEntity(Game::get()->getCharacterId()).get();
    TransformComponent* tc = static_cast<TransformComponent*>(character->components[ComponentType::Transform].get());

    posX.setText(std::string("Position X: ") + std::to_string(tc->position.x));
    posY.setText(std::string("Position Y: ") + std::to_string(tc->position.y));
    posZ.setText(std::string("Position Z: ") + std::to_string(tc->position.z));
    Scene2D::draw(dt);
}

void DebugHUD::update(float dt) {

}

void DebugHUD::trigger() {
//    visible = !visible;
}

void DebugHUD::onWindowResize(int width, int height) {
//    resize(width, height);
}

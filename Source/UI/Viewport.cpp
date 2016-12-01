#include "Viewport.h"
#include "../Event/Event.h"
#include "../ECS/Engine.h"
#include "../ECS/Systems/Systems.h"
#include <SDL_opengl.h>
#include <algorithm>

Viewport::Viewport() {
    switchCameras[0] = nullptr;
    switchCameras[1] = nullptr;
    setBackgroundColor(glm::vec4(0.77, 0.83, 0.83, 1.0));
}

void Viewport::update(double dt) {

}

void Viewport::draw(float dt) {
}

void Viewport::setBackgroundColor(const glm::vec4& backgroundColor) {
    this->backgroundColor = backgroundColor;
//    glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
}

void Viewport::setRectangle(int x, int y, int width, int height) {
//    glViewport(x, y, width, height);
}

void Viewport::addCamera(std::shared_ptr<Entity> camera) {
    cameras.push_back(camera);
}

void Viewport::removeCamera(std::shared_ptr<Entity> camera) {
    cameras.erase(std::remove(cameras.begin(), cameras.end(), camera), cameras.end());
}

void Viewport::clearCameras() {
    cameras.clear();
}

void Viewport::setCurrentCamera(std::shared_ptr<Entity> currentCamera) {
    this->currentCamera = currentCamera;
    MovementControllerSystem* movementControllerSystem = static_cast<MovementControllerSystem*>(Engine::get()->getSystem(SystemType::MovementController).get());
    movementControllerSystem->setMoveEntity(currentCamera.get());
    movementControllerSystem->setRotateEntity(currentCamera.get());

    switchCameras[1] = switchCameras[0];
    switchCameras[0] = currentCamera;
}

void Viewport::switchCamera() {
    if (switchCameras[1] != nullptr) {
        setCurrentCamera(switchCameras[1]);
    }
}

#include "Viewport.h"
#include "../Event/Event.h"
#include "../ECS/Engine.h"
#include "../ECS/Systems/Systems.h"
#include <SDL_opengl.h>
#include <algorithm>

Viewport::Viewport() {
}

void Viewport::update(double dt) {

}

void Viewport::draw(float dt) {
}

void Viewport::setBackgroundColor(const glm::vec4& backgroundColor) {
    this->backgroundColor = backgroundColor;
    glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
}

void Viewport::setRectangle(int x, int y, int width, int height) {
    glViewport(x, y, width, height);
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
    MovementControllerSystem* movementControllerSystem = static_cast<MovementControllerSystem*>(Engine::getInstance()->getSystem(SystemType::MovementController).get());
    movementControllerSystem->setMoveEntity(currentCamera.get());
    movementControllerSystem->setRotateEntity(currentCamera.get());
}

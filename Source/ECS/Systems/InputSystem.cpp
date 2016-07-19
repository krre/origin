#include "InputSystem.h"
#include "TransformSystem.h"
#include "../ECS/Engine.h"
#include "../Core/Game.h"
#include "../Event/Input.h"
#include "../Components/TransformComponent.h"
#include "../Components/MovementComponent.h"

InputSystem::InputSystem() {
    type = System::Type::Input;
}

void InputSystem::process(float dt) {
    if (Game::getInstance()->getState() == Game::PAUSE) return;
    Game::getInstance()->cameraMove(dt); // TODO: remove
    if (activeEntity) {
        moveActiveEntity(dt);
    }
}

void InputSystem::setActiveEntity(std::shared_ptr<Entity> activeEntity) {
    this->activeEntity = activeEntity;
}

void InputSystem::moveActiveEntity(float dt) {
    MovementComponent* mc = static_cast<MovementComponent*>(activeEntity->getComponent(Component::Type::Movement));
    TransformComponent* tc = static_cast<TransformComponent*>(activeEntity->getComponent(Component::Type::Transform));

    glm::ivec2 relMousePos = Input::getInstance()->getRelMousePos();
    tc->yaw += mc->rotateSpeed * relMousePos.x;
    tc->yaw = fmod(tc->yaw, 360.0f);

    tc->pitch -= mc->rotateSpeed * relMousePos.y;
    tc->pitch = glm::clamp(tc->pitch, -80.0f, 80.0f);

    glm::quat rotation = glm::toQuat(glm::eulerAngleYX(glm::radians(tc->yaw), glm::radians(tc->pitch)));
    TransformSystem* transformSystem = static_cast<TransformSystem*>(Engine::getInstance()->getSystem(System::Type::Transform).get());
    transformSystem->setRotation(activeEntity, rotation);

    if (Input::getInstance()->isKeyPressed(SDLK_w)) {
        transformSystem->translate(activeEntity, glm::vec3(0.0f, 0.0f, -1.0f) * mc->moveSpeed * dt);
    } else if (Input::getInstance()->isKeyPressed(SDLK_s)) {
        transformSystem->translate(activeEntity, glm::vec3(0.0f, 0.0f, 1.0f) * mc->moveSpeed * dt);
    } else if (Input::getInstance()->isKeyPressed(SDLK_a)) {
        transformSystem->translate(activeEntity, glm::vec3(-1.0f, 0.0f, 0.0f) * mc->moveSpeed * dt);
    } else if (Input::getInstance()->isKeyPressed(SDLK_d)) {
        transformSystem->translate(activeEntity, glm::vec3(1.0f, 0.0f, 0.0f) * mc->moveSpeed * dt);
    }
}

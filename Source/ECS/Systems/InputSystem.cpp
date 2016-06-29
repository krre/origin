#include "InputSystem.h"
#include "../ECS/Engine.h"

InputSystem::InputSystem() {
    type = SystemType::Input;
}

void InputSystem::process(float dt) {
    for (auto entity: Engine::getInstance()->getEntities()) {
        if (entity->getComponent(ComponentType::Input)) {

        }
    }
}

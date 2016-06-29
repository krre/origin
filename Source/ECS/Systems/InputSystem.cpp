#include "InputSystem.h"
#include "../ECS/Engine.h"

InputSystem::InputSystem() {

}

void InputSystem::process(float dt) {
    for (auto entity: Engine::getInstance()->getEntities()) {
        if (entity->getComponent(ComponentType::Input)) {

        }
    }
}

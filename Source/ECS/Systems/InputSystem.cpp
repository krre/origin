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

}

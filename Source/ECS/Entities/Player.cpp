#include "Player.h"
#include "../ECS/Components/CameraComponent.h"
#include "../ECS/Components/NodeComponent.h"
#include "../ECS/Components/TransformComponent.h"
#include "../ECS/Components/InputComponent.h"
#include "../Graphics/Camera.h"

Player::Player() {
    addComponent<NodeComponent>();
    addComponent<TransformComponent>();
    addComponent<InputComponent>();

    CameraComponent* cameraComponent = addComponent<CameraComponent>();
    cameraComponent->camera = shared_ptr<Camera>(new Camera());
}

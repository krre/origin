#include "Player.h"
#include "../ECS/Components/CameraComponent.h"
#include "../Graphics/Camera.h"

Player::Player() {
    addComponent(ComponentType::Node);
    addComponent(ComponentType::Transform);

    CameraComponent* cameraComponent = static_cast<CameraComponent*>(addComponent(ComponentType::Camera));
    cameraComponent->camera = new Camera();
}

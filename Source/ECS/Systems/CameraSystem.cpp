#include "CameraSystem.h"
#include "TransformSystem.h"
#include "../Components/CameraComponent.h"
#include "../Components/TransformComponent.h"

CameraSystem::CameraSystem() {
    type = System::Type::Camera;
}

void CameraSystem::process(float dt) {

}

glm::mat4 CameraSystem::getView(Entity* entity) {
    TransformComponent* tc = static_cast<TransformComponent*>(entity->components[Component::Type::Transform].get());
//    return glm::inverse(cc->worldMatrix);;
    glm::mat4 translate = glm::translate(-tc->translation);
    glm::mat4 rotate = glm::transpose(glm::toMat4(tc->rotation));
    return rotate * translate;
}

glm::mat4 CameraSystem::getProjection(Entity* entity) {
    CameraComponent* cc = static_cast<CameraComponent*>(entity->components[Component::Type::Camera].get());
    return cc->camera->getProjection();
}

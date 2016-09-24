#include "CameraSystem.h"
#include "../../Event/Event.h"
#include "TransformSystem.h"
#include "../../ECS/Engine.h"
#include "../Components/CameraComponent.h"
#include "../Components/TransformComponent.h"

CameraSystem::CameraSystem() {
    type = SystemType::Camera;
    Event::getInstance()->windowResize.connect<CameraSystem, &CameraSystem::onWindowResize>(this);
}

void CameraSystem::process(float dt) {

}

glm::mat4 CameraSystem::getView(Entity* entity) {
    TransformComponent* tc = static_cast<TransformComponent*>(entity->components[ComponentType::Transform].get());
//    return glm::inverse(cc->worldMatrix);;
    glm::mat4 translate = glm::translate(-tc->position);
    glm::mat4 rotate = glm::transpose(glm::toMat4(tc->rotation));
    return rotate * translate;
}

void CameraSystem::onWindowResize(int width, int height) {
    // TODO: Replace by family
    for (auto entity : engine->getEntities()) {
        CameraComponent* cameraComp = static_cast<CameraComponent*>(entity->components[ComponentType::Camera].get());
        if (cameraComp) {
            cameraComp->aspect = width * 1.0f / height;
            cameraComp->projection = glm::perspective(cameraComp->fov, cameraComp->aspect, cameraComp->near, cameraComp->far);
        }
    }
}

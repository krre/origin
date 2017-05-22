#include "CameraSystem.h"
#include "Event/Event.h"
#include "TransformSystem.h"
#include "ECS/EntityManager.h"
#include "ECS/Entity.h"
#include "ECS/Components/CameraComponent.h"
#include "ECS/Components/TransformComponent.h"

CameraSystem::CameraSystem() {
    type = SystemType::Camera;
    Event::get()->windowResize.connect<CameraSystem, &CameraSystem::onWindowResize>(this);
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
    for (const auto& entity : entityManager->getEntities()) {
        CameraComponent* cameraComp = static_cast<CameraComponent*>(entity.second->components[ComponentType::Camera].get());
        if (cameraComp) {
            cameraComp->aspect = width * 1.0f / height;
            cameraComp->projection = glm::perspective(cameraComp->fov, cameraComp->aspect, cameraComp->near, cameraComp->far);
        }
    }
}

#include "CameraSystem.h"
#include "Event/Event.h"
#include "TransformSystem.h"
#include "ECS/EntityManager.h"
#include "ECS/Entity.h"
#include "ECS/Components/CameraComponent.h"
#include "ECS/Components/TransformComponent.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace Origin {

CameraSystem::CameraSystem(EntityManager* entityManager) : System(entityManager) {
    type = System::Type::Camera;
    Event::get()->windowResize.connect(this, &CameraSystem::onWindowResize);
}

void CameraSystem::process(float dt) {

}

glm::mat4 CameraSystem::getView(Entity* entity) {
    TransformComponent* tc = entity->getTransform();
//    return glm::inverse(cc->worldMatrix);;
    glm::mat4 mat(1);
    glm::mat4 translate = glm::translate(mat, -tc->position);
    glm::mat4 rotate = glm::transpose(glm::toMat4(tc->rotation));
    return rotate * translate;
}

void CameraSystem::onWindowResize(int width, int height) {
    // TODO: Replace by family
    for (const auto& entity : entityManager->getEntities()) {
        CameraComponent* cameraComp = entity.second->getCamera();
        if (cameraComp) {
            cameraComp->aspect = width * 1.0f / height;
            cameraComp->projection = glm::perspective(cameraComp->fov, cameraComp->aspect, cameraComp->near, cameraComp->far);
        }
    }
}

} // Origin

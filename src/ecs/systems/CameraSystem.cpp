#include "CameraSystem.h"
#include "event/Event.h"
#include "TransformSystem.h"
#include "ecs/EntityManager.h"
#include "ecs/Entity.h"
#include "ecs/components/CameraComponent.h"
#include "ecs/components/TransformComponent.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

CameraSystem::CameraSystem(EntityManager* entityManager) : System(entityManager) {
    m_type = System::Type::Camera;
    Event::get()->windowResize.connect(this, &CameraSystem::onWindowResize);
}

void CameraSystem::process(float dt) {

}

glm::mat4 CameraSystem::view(Entity* entity) {
    TransformComponent* tc = entity->transform();
//    return glm::inverse(cc->worldMatrix);;
    glm::mat4 mat(1);
    glm::mat4 translate = glm::translate(mat, -tc->position);
    glm::mat4 rotate = glm::transpose(glm::toMat4(tc->rotation));
    return rotate * translate;
}

void CameraSystem::onWindowResize(int width, int height) {
    // TODO: Replace by family
    for (const auto& entity : m_entityManager->entities()) {
        CameraComponent* cameraComp = entity.second->camera();
        if (cameraComp) {
            cameraComp->aspect = width * 1.0f / height;
            cameraComp->projection = glm::perspective(cameraComp->fov, cameraComp->aspect, cameraComp->near, cameraComp->far);
        }
    }
}

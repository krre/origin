#include "Renderer.h"
#include "../Core/App.h"
#include "../Resource/ResourceManager.h"
#include "../ECS/Components/Components.h"
#include "../ECS/Engine.h"
#include "../ECS/Systems/CameraSystem.h"
#include "../Core/Game.h"
#include <SDL_opengl.h>
#include <assert.h>

Renderer::Renderer() {

}

void Renderer::render(Entity* entity) {
    Entity* currentCamera = App::getInstance()->getViewport()->getCurrentCamera().get();
    CameraComponent* cameraComp = static_cast<CameraComponent*>(currentCamera->components[ComponentType::Camera].get());
    TransformComponent* cameraTransform = static_cast<TransformComponent*>(currentCamera->components[ComponentType::Transform].get());

    TransformComponent* transformComp = static_cast<TransformComponent*>(entity->components[ComponentType::Transform].get());
    OctreeComponent* octreeComp = static_cast<OctreeComponent*>(entity->components[ComponentType::Octree].get());
    MaterialComponent* materialComp = static_cast<MaterialComponent*>(entity->components[ComponentType::Material].get());

    glm::vec3 materialColor = materialComp->color;
    glm::vec3 cameraPos = cameraTransform->position;
    CameraSystem* cameraSystem = static_cast<CameraSystem*>(Engine::getInstance()->getSystem(SystemType::Camera).get());

    glm::mat4 projection = cameraComp->projection;
    glm::mat4 view = cameraSystem->getView(currentCamera);
    glm::mat4 modelMatrix = transformComp->worldMatrix;
    glm::mat4 mvpMatrix = projection * view * modelMatrix;

    octreeComp->octree->draw();
}

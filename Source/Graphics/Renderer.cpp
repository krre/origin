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
    bool wireframe = Game::getInstance()->getWireframe();
    if (wireframe) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    Entity* currentCamera = App::getInstance()->getViewport()->getCurrentCamera().get();
    CameraComponent* cameraComp = static_cast<CameraComponent*>(currentCamera->components[Component::Type::Camera].get());
    TransformComponent* transformComp = static_cast<TransformComponent*>(entity->components[Component::Type::Transform].get());
    MeshComponent* meshComp = static_cast<MeshComponent*>(entity->components[Component::Type::Mesh].get());
    MaterialComponent* materialComp = static_cast<MaterialComponent*>(entity->components[Component::Type::Material].get());

    ShaderGroup* shaderGroup = ResourceManager::getInstance()->getShaderGroup("BaseShaderGroup");
    shaderGroup->use();

    GLuint matrix = glGetUniformLocation(shaderGroup->getProgram(), "mvp");
    CameraSystem* cameraSystem = static_cast<CameraSystem*>(Engine::getInstance()->getSystem(System::Type::Camera).get());

    glm::mat4 projection = cameraComp->projection;
    glm::mat4 view = cameraSystem->getView(currentCamera);
    glm::mat4 modelMatrix = transformComp->worldMatrix;
    glm::mat4 mvp = projection * view * modelMatrix;
    glUniformMatrix4fv(matrix, 1, GL_FALSE, &mvp[0][0]);

    GLuint color = glGetUniformLocation(shaderGroup->getProgram(), "color");
    glm::vec3 c = materialComp->material->getColor().getRgb();
    glUniform3fv(color, 1, &c[0]);

    meshComp->mesh->draw();

    if (wireframe) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}

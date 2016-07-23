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
    CameraComponent* cameraComp = static_cast<CameraComponent*>(currentCamera->components[ComponentType::Camera].get());
    TransformComponent* cameraTransform = static_cast<TransformComponent*>(currentCamera->components[ComponentType::Transform].get());

    TransformComponent* transformComp = static_cast<TransformComponent*>(entity->components[ComponentType::Transform].get());
    MeshComponent* meshComp = static_cast<MeshComponent*>(entity->components[ComponentType::Mesh].get());
    MaterialComponent* materialComp = static_cast<MaterialComponent*>(entity->components[ComponentType::Material].get());

    ShaderGroup* shaderGroup = ResourceManager::getInstance()->getShaderGroup("LightShaderGroup");
    shaderGroup->use();

    GLint objectColor = glGetUniformLocation(shaderGroup->getProgram(), "objectColor");
    GLint lightColor  = glGetUniformLocation(shaderGroup->getProgram(), "lightColor");
    GLint lightPos    = glGetUniformLocation(shaderGroup->getProgram(), "lightPos");
    GLint viewPos     = glGetUniformLocation(shaderGroup->getProgram(), "viewPos");
    GLuint mvp        = glGetUniformLocation(shaderGroup->getProgram(), "mvp");
    GLuint model      = glGetUniformLocation(shaderGroup->getProgram(), "model");

    glm::vec3 color = materialComp->color;
    glm::vec3 cameraPos = cameraTransform->position;
    CameraSystem* cameraSystem = static_cast<CameraSystem*>(Engine::getInstance()->getSystem(SystemType::Camera).get());

    glm::mat4 projection = cameraComp->projection;
    glm::mat4 view = cameraSystem->getView(currentCamera);
    glm::mat4 modelMatrix = transformComp->worldMatrix;
    glm::mat4 mvpMatrix = projection * view * modelMatrix;

    glUniform3f(objectColor, color.r, color.g, color.b);
    glUniform3f(lightColor, 1.0f, 1.0f, 1.0f);
    glUniform3f(lightPos, -0.5f, 1.0f, 0.3f);
    glUniform3f(viewPos, cameraPos.x, cameraPos.y, cameraPos.z);
    glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glUniformMatrix4fv(mvp, 1, GL_FALSE, glm::value_ptr(mvpMatrix));

    meshComp->mesh->draw();

    if (wireframe) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}

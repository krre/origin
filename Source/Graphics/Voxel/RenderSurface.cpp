#include "RenderSurface.h"
#include "../Resource/ResourceManager.h"
#include "Octree.h"
#include "../Core/App.h"
#include "../ECS/Components/Components.h"
#include "../ECS/Systems/CameraSystem.h"
#include "../ECS/Engine.h"
#include "../Core/Common.h"
#include "../Core/Utils.h"
#include <glm/gtx/matrix_decompose.hpp>

RenderSurface::RenderSurface() :
    octreeToWorldTexture(GL_TEXTURE_BUFFER),
    vbo(GL_ARRAY_BUFFER),
    tbo(GL_TEXTURE_BUFFER) {

    voxelShaderGroup = ResourceManager::getInstance()->getShaderGroup("VoxelShaderGroup");
    program = voxelShaderGroup->getProgram();
    voxelShaderGroup->use();

    glm::vec3 aabbMin = glm::vec3(-1.0, -1.0, -1.0);
    glm::vec3 aabbMax = glm::vec3(1.0, 1.0, 1.0);

    glUniform3fv(glGetUniformLocation(program, "aabb.min"), 1, &aabbMin[0]);
    glUniform3fv(glGetUniformLocation(program, "aabb.max"), 1, &aabbMax[0]);

    GLfloat vertices[] = {
        -1.0f,  1.0f,
        -1.0f, -1.0f,
         1.0f,  1.0f,

        -1.0f, -1.0f,
         1.0f, -1.0f,
         1.0f,  1.0f,
    };

    vao.bind();

    vbo.bind();
    vbo.setData(vertices, sizeof(vertices));

    // Position attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    vao.unbind();

    tbo.bind();
    glBufferData(GL_TEXTURE_BUFFER, sizeof(glm::vec4) * 8 * MAX_OCTREE_COUNT, NULL, GL_STATIC_DRAW);
    tbo.unbind();

    octreeToWorldTexture.bind();
    octreeToWorldTexture.attachBuffer(GL_RGBA32F, tbo.getId());
    octreeToWorldTexture.unbind();
}

void RenderSurface::draw(float dt) {
    int width = App::getInstance()->getWidth();
    int height = App::getInstance()->getHeight();

    Entity* currentCamera = App::getInstance()->getViewport()->getCurrentCamera().get();
    CameraComponent* cameraComp = static_cast<CameraComponent*>(currentCamera->components[ComponentType::Camera].get());
    TransformComponent* cameraTransform = static_cast<TransformComponent*>(currentCamera->components[ComponentType::Transform].get());

    Octree* octree;
    TransformComponent* octreeTransform;
    MaterialComponent* octreeMaterial;
    glm::vec3 octreeColor;

    TransformComponent* lightTransform;
    glm::vec3 lightColor = glm::vec3(0.0);
    glm::vec3 lightPos = glm::vec3(0.0);

    // TODO: Replace by family
    for (auto entity : Engine::getInstance()->getEntities()) {
        OctreeComponent* octreeComp = static_cast<OctreeComponent*>(entity->components[ComponentType::Octree].get());
        if (octreeComp) {
            octree = octreeComp->octree.get();
            octreeTransform = static_cast<TransformComponent*>(entity->components[ComponentType::Transform].get());
            octreeMaterial = static_cast<MaterialComponent*>(entity->components[ComponentType::Material].get());
            octreeColor = octreeMaterial->color;
        }

        LightComponent* lightComp = static_cast<LightComponent*>(entity->components[ComponentType::Light].get());
        if (lightComp) {
            lightTransform = static_cast<TransformComponent*>(entity->components[ComponentType::Transform].get());
            lightColor = lightComp->color;
            lightPos = glm::vec3(lightTransform->objectToWorld[3]);
        }
    }

    // TODO: Replace by family
    std::vector<glm::vec4> octrees;
    int octreeCount = 0;
    for (auto entity : Engine::getInstance()->getEntities()) {
        OctreeComponent* octreeComp = static_cast<OctreeComponent*>(entity->components[ComponentType::Octree].get());
        if (octreeComp) {
//            Octree* octree = octreeComp->octree.get();
            TransformComponent* octreeTransform = static_cast<TransformComponent*>(entity->components[ComponentType::Transform].get());
            octrees.push_back(octreeTransform->objectToWorld[0]);
            octrees.push_back(octreeTransform->objectToWorld[1]);
            octrees.push_back(octreeTransform->objectToWorld[2]);
            octrees.push_back(octreeTransform->objectToWorld[3]);
//            MaterialComponent* octreeMaterial = static_cast<MaterialComponent*>(entity->components[ComponentType::Material].get());
//            glm::vec3 octreeColor = octreeMaterial->color;

            glm::mat4 cameraToObject = octreeTransform->worldToObject * cameraTransform->objectToWorld;

            glm::vec3 scale;
            glm::quat rotation;
            glm::vec3 translation;
            glm::vec3 skew;
            glm::vec4 perspective;
            glm::decompose(cameraToObject, scale, rotation, translation, skew, perspective);

            octrees.push_back(glm::vec4(translation.x, translation.y, translation.z, 1.0));

            glm::vec3 up = cameraComp->up * rotation;
            glm::vec3 look = cameraComp->look * rotation;
            glm::vec3 right = cameraComp->right * rotation;

            // Ray calculation is based on Johns Hopkins presentation:
            // http://www.cs.jhu.edu/~cohen/RendTech99/Lectures/Ray_Casting.bw.pdf
            glm::vec3 h0 = look - up * glm::tan(cameraComp->fov); // min height vector
            glm::vec3 h1 = look + up * glm::tan(cameraComp->fov); // max height vector
            glm::vec3 stepH = (h1 - h0) / height;
            h0 += stepH / 2;

            glm::vec3 w0 = look - right * glm::tan(cameraComp->fov) * width / height; // min width vector
            glm::vec3 w1 = look + right * glm::tan(cameraComp->fov) * width / height; // max width vector
            glm::vec3 stepW = (w1 - w0) / width;
            w0 += stepW / 2;

            glm::vec3 startCornerPos = w0 + h0;

            octrees.push_back(glm::vec4(startCornerPos.x, startCornerPos.y, startCornerPos.z, 0.0));
            octrees.push_back(glm::vec4(stepW.x, stepW.y, stepW.z, 0.0));
            octrees.push_back(glm::vec4(stepH.x, stepH.y, stepH.z, 0.0));

            octreeCount++;
        }
    }

    tbo.bind();
    glBufferSubData(GL_TEXTURE_BUFFER, 0, sizeof(glm::vec4) * octrees.size(), &octrees[0]);
    tbo.unbind();

    glm::vec4 bgColor = App::getInstance()->getViewport()->getBackgroundColor();

    float ambientStrength = 0.1f;

    voxelShaderGroup->use();

    glUniform3fv(glGetUniformLocation(program, "backgroundColor"), 1, &bgColor[0]);
    glUniform3fv(glGetUniformLocation(program, "octreeColor"), 1, &octreeColor[0]);
    glUniform3fv(glGetUniformLocation(program, "lightColor"), 1, &lightColor[0]);
    glUniform3fv(glGetUniformLocation(program, "lightPos"), 1, &lightPos[0]);
    glUniform1f(glGetUniformLocation(program, "ambientStrength"), ambientStrength);
    glUniform1f(glGetUniformLocation(program, "octrees"), 0);
    glUniform1i(glGetUniformLocation(program, "octreeCount"), octreeCount);

    glActiveTexture(GL_TEXTURE0);
    octreeToWorldTexture.bind();

    vao.bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);
    vao.unbind();
}


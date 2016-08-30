#include "OctreeRenderer.h"
#include "RenderSurface.h"
#include "../Core/App.h"
#include "../ECS/Components/Components.h"
#include "../ECS/Systems/CameraSystem.h"
#include "../ECS/Engine.h"
#include "../Resource/ResourceManager.h"
#include "../Core/Common.h"
#include "../Core/Utils.h"
#include <glm/gtx/matrix_decompose.hpp>

OctreeRenderer::OctreeRenderer() {

}

void OctreeRenderer::render(const RenderSurface* renderSurface) {
//    if (renderOnlyFirst) return;
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
            lightPos = glm::vec3(lightTransform->worldMatrix[3]);
        }
    }

    uint32* data = renderSurface->getData();
    int width = renderSurface->getWidth();
    int height = renderSurface->getHeight();

    Entity* currentCamera = App::getInstance()->getViewport()->getCurrentCamera().get();
    CameraComponent* cameraComp = static_cast<CameraComponent*>(currentCamera->components[ComponentType::Camera].get());
    TransformComponent* cameraTransform = static_cast<TransformComponent*>(currentCamera->components[ComponentType::Transform].get());

    glm::mat4 worldToObject = glm::inverse(octreeTransform->worldMatrix);
    glm::mat4 cameraToObject = worldToObject * cameraTransform->worldMatrix;

    glm::vec3 scale;
    glm::quat rotation;
    glm::vec3 translation;
    glm::vec3 skew;
    glm::vec4 perspective;
    glm::decompose(cameraToObject, scale, rotation, translation, skew, perspective);

    Ray ray;
    ray.origin = translation;

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

    AABB aabb;
    aabb.min = glm::vec3(-1.0, -1.0, -1.0);
    aabb.max = glm::vec3(1.0, 1.0, 1.0);

    glm::vec4 bgColor = App::getInstance()->getViewport()->getBackgroundColor();
    uint32 bgColorPack = Utils::rgbaToUint32(bgColor);
    uint32 octreeColorPack = Utils::rgbaToUint32(glm::vec4(octreeColor.r, octreeColor.g, octreeColor.b, 1.0));

    if (App::getInstance()->getRendererType() == RendererType::GPU) {
        ShaderGroup* voxelShaderGroup = ResourceManager::getInstance()->getShaderGroup("VoxelShaderGroup");
        voxelShaderGroup->use();

        glUniform3f(glGetUniformLocation(voxelShaderGroup->getProgram(), "backgroundColor"), bgColor.r, bgColor.g, bgColor.b);
        glUniform3f(glGetUniformLocation(voxelShaderGroup->getProgram(), "octreeColor"), octreeColor.r, octreeColor.g, octreeColor.b);
        glUniform3f(glGetUniformLocation(voxelShaderGroup->getProgram(), "lightColor"), lightColor.r, lightColor.g, lightColor.b);
        glUniform3f(glGetUniformLocation(voxelShaderGroup->getProgram(), "lightPos"), lightPos.x, lightPos.y, lightPos.z);
        glUniformMatrix4fv(glGetUniformLocation(voxelShaderGroup->getProgram(), "cameraMat"), 1, GL_FALSE, glm::value_ptr(cameraTransform->worldMatrix));
        glUniform3f(glGetUniformLocation(voxelShaderGroup->getProgram(), "cameraPos"), translation.x, translation.y, translation.z);
    //    glProgramUniform3fv(glGetUniformLocation(voxelShaderGroup->getProgram(), "aabb.min"), 1, glm::value_ptr(aabb.min));

        glUniform3f(glGetUniformLocation(voxelShaderGroup->getProgram(), "w0"), w0.x, w0.y, w0.z);
        glUniform3f(glGetUniformLocation(voxelShaderGroup->getProgram(), "h0"), h0.x, h0.y, h0.z);
        glUniform3f(glGetUniformLocation(voxelShaderGroup->getProgram(), "stepW"), stepW.x, stepW.y, stepW.z);
        glUniform3f(glGetUniformLocation(voxelShaderGroup->getProgram(), "stepH"), stepH.x, stepH.y, stepH.z);

        glUniform3f(glGetUniformLocation(voxelShaderGroup->getProgram(), "aabbMin"), aabb.min.x, aabb.min.y, aabb.min.z);
        glUniform3f(glGetUniformLocation(voxelShaderGroup->getProgram(), "aabbMax"), aabb.max.x, aabb.max.y, aabb.max.z);
    } else {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                ray.direction = glm::normalize(w0 + stepW * x + h0 + stepH * y);
                float t;
                if (rayAABBIntersect(&ray, &aabb, t)) {
                    glm::vec3 hitPointObject = ray.origin + ray.direction * t;
                    float fixPrecision = 0.00001; // for fix numbers 0.9999999 to 1.0
                    glm::vec3 hitNormalObject = glm::vec3(int(hitPointObject.x + fixPrecision), int(hitPointObject.y + fixPrecision), int(hitPointObject.z + fixPrecision));
                    glm::vec3 hitPointWorld = glm::vec3(octreeTransform->worldMatrix * glm::vec4(hitPointObject.x, hitPointObject.y, hitPointObject.z, 1.0));
                    glm::vec3 hitNormalWorld = glm::normalize(glm::vec3(octreeTransform->worldMatrix * glm::vec4(hitNormalObject.x, hitNormalObject.y, hitNormalObject.z, 0.0)));
//                    print(x << "|" << y << "|" << glm::to_string(hitPointObject));
//                    print(x << "|" << y << "|" << glm::to_string(hitNormalObject));
//                    print(x << "|" << y << "|" << glm::to_string(hitPointWorld));
//                    print(x << "|" << y << "|" << glm::to_string(hitNormalWorld));
                    glm::vec3 color = glm::dot(hitNormalWorld, glm::normalize(lightPos)) * octreeColor;
                    data[y * width + x] = Utils::rgbaToUint32(glm::vec4(color.r, color.g, color.b, 1.0));; // objects color
                } else {
                    data[y * width + x] = bgColorPack; // background color
                }
            }
        }
    }

    renderOnlyFirst = true;
}

bool OctreeRenderer::rayAABBIntersect(Ray* ray, AABB* aabb, float& t) {
    float loX = (aabb->min.x - ray->origin.x) / ray->direction.x;
    float hiX = (aabb->max.x - ray->origin.x) / ray->direction.x;

    float tmin = std::min(loX, hiX);
    float tmax = std::max(loX, hiX);

    float loY = (aabb->min.y - ray->origin.y) / ray->direction.y;
    float hiY = (aabb->max.y - ray->origin.y) / ray->direction.y;

    tmin = std::max(tmin, std::min(loY, hiY));
    tmax = std::min(tmax, std::max(loY, hiY));

    float loZ = (aabb->min.z - ray->origin.z) / ray->direction.z;
    float hiZ = (aabb->max.z - ray->origin.z) / ray->direction.z;

    tmin = std::max(tmin, std::min(loZ, hiZ));
    tmax = std::min(tmax, std::max(loZ, hiZ));
    t = tmin;
    return (tmin <= tmax) && (tmax > 0.0f);
}

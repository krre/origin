#include "OctreeRenderer.h"
#include "RenderSurface.h"
#include "../Core/App.h"
#include "../ECS/Components/Components.h"
#include "../ECS/Systems/CameraSystem.h"
#include "../ECS/Engine.h"
#include "../Resource/ResourceManager.h"
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

    glm::vec3 scale;
    glm::quat rotation;
    glm::vec3 translation;
    glm::vec3 skew;
    glm::vec4 perspective;
    glm::decompose(cameraTransform->worldMatrix, scale, rotation, translation, skew, perspective);

    glm::vec3 up = cameraComp->up * rotation;
    glm::vec3 look = cameraComp->look * rotation;
    glm::vec3 right = cameraComp->right * rotation;

    Ray ray;
    ray.origin = translation;

//    glm::mat4 invMatrix = glm::translate(glm::mat4(1.0), -ray.origin) * glm::inverse(glm::mat4(cameraTransform->rotation));
//    invMatrix = glm::translate(invMatrix, ray.origin);
//    ray.origin = glm::vec3(invMatrix * glm::vec4(ray.origin.x, ray.origin.y, ray.origin.z, 1.0));

    // Ray calculation is based on Johns Hopkins presentation:
    // http://www.cs.jhu.edu/~cohen/RendTech99/Lectures/Ray_Casting.bw.pdf
    glm::vec3 h0 = look - up * glm::tan(cameraComp->fov); // min height vector
    glm::vec3 h1 = look + up * glm::tan(cameraComp->fov); // max height vector
    glm::vec3 stepH = (h1 - h0) / height;

    glm::vec3 w0 = look - right * glm::tan(cameraComp->fov) * width / height; // min width vector
    glm::vec3 w1 = look + right * glm::tan(cameraComp->fov) * width / height; // max width vector
    glm::vec3 stepW = (w1 - w0) / width;

    AABB aabb;
    aabb.min = glm::vec3(octreeTransform->worldMatrix * glm::vec4(-1.0, -1.0, -1.0, 1.0));
    aabb.max = glm::vec3(octreeTransform->worldMatrix * glm::vec4( 1.0,  1.0,  1.0, 1.0));

    glm::vec3 directionW;
    glm::vec3 directionH = h0 - stepH / 2; // start height vector (from bottom to up)

    ShaderGroup* voxelShaderGroup = ResourceManager::getInstance()->getShaderGroup("VoxelShaderGroup");
    GLuint cameraMat = glGetUniformLocation(voxelShaderGroup->getProgram(), "cameraMat");
    GLint cameraPos = glGetUniformLocation(voxelShaderGroup->getProgram(), "cameraPos");

    glUniformMatrix4fv(cameraMat, 1, GL_FALSE, glm::value_ptr(cameraTransform->worldMatrix));
    glUniform3f(cameraPos, translation.x, translation.y, translation.z);

    for (int y = 0; y < height; y++) {
        directionH = directionH + stepH;
        directionW = w0 - stepW / 2; // start width vector (from left to right)
        for (int x = 0; x < width; x++) {
            directionW = directionW + stepW;

            ray.direction = glm::normalize(directionW + directionH);
//            ray.direction = glm::vec3(invMatrix * glm::vec4(ray.direction.x, ray.direction.y, ray.direction.z, 0.0));

            if (rayAABBIntersect(&ray, &aabb)) {
                data[y * width + x] = 0x94510eff; // objects color
            } else {
                data[y * width + x] = 0xc4d3d3ff; // background color
            }
        }
    }

    renderOnlyFirst = true;
}

bool OctreeRenderer::rayAABBIntersect(Ray* ray, AABB* aabb) {
    float tmin, tmax, tymin, tymax, tzmin, tzmax;

    glm::vec3 bounds[2];
    bounds[0] = aabb->min;
    bounds[1] = aabb->max;

    glm::vec3 invdir = 1.0f / ray->direction;
    glm::i8vec3 sign;

    sign.x = (invdir.x < 0);
    sign.y = (invdir.y < 0);
    sign.z = (invdir.z < 0);

    tmin = (bounds[sign.x].x - ray->origin.x) * invdir.x;
    tmax = (bounds[1 - sign.x].x - ray->origin.x) * invdir.x;
    tymin = (bounds[sign.y].y - ray->origin.y) * invdir.y;
    tymax = (bounds[1 - sign.y].y - ray->origin.y) * invdir.y;

    if ((tmin > tymax) || (tymin > tmax)) {
        return false;
    }

    if (tymin > tmin) {
        tmin = tymin;
    }

    if (tymax < tmax) {
        tmax = tymax;
    }

    tzmin = (bounds[sign.z].z - ray->origin.z) * invdir.z;
    tzmax = (bounds[1 - sign.z].z - ray->origin.z) * invdir.z;

    if ((tmin > tzmax) || (tzmin > tmax)) {
        return false;
    }

    if (tzmin > tmin) {
        tmin = tzmin;
    }

    if (tzmax < tmax) {
        tmax = tzmax;
    }

    return true;
}

#include "OctreeRenderer.h"
#include "RenderSurface.h"
#include "../Core/App.h"
#include "../ECS/Components/Components.h"
#include "../ECS/Systems/CameraSystem.h"
#include "../ECS/Engine.h"
#include <glm/gtx/matrix_decompose.hpp>

OctreeRenderer::OctreeRenderer() {

}

void OctreeRenderer::render(const RenderSurface* renderSurface) {
//    if (renderOnlyFirst) return;
    Octree* octree;
    TransformComponent* transformComp;
    // TODO: Replace by family
    for (auto entity : Engine::getInstance()->getEntities()) {
        OctreeComponent* octreeComp = static_cast<OctreeComponent*>(entity->components[ComponentType::Octree].get());
        if (octreeComp) {
            octree = octreeComp->octree.get();
            transformComp = static_cast<TransformComponent*>(entity->components[ComponentType::Transform].get());
            break;
        }
    }

    uint32* data = renderSurface->getData();
    int width = renderSurface->getWidth();
    int height = renderSurface->getHeight();

    glm::vec3 scale;
    glm::quat rotation;
    glm::vec3 translation;
    glm::vec3 skew;
    glm::vec4 perspective;
    glm::decompose(transformComp->worldMatrix, scale, rotation, translation, skew, perspective);
    glm::mat4 invRotationMatrix = glm::inverse(glm::toMat4(rotation));

    Ray ray;
    ray.origin.z = 1.0;
    ray.direction = glm::vec3(invRotationMatrix * glm::vec4(0.0, 0.0, -1.0, 0.0));

    AABB aabb;
    aabb.min = glm::vec3(transformComp->worldMatrix * glm::vec4(-1.0, -1.0, -1.0, 1.0));
    aabb.max = glm::vec3(transformComp->worldMatrix * glm::vec4( 1.0,  1.0,  1.0, 1.0));

    for (int y = 0; y < height; y++) {
        float yNorm = 1.0f - (2.0f * y) / height;
        for (int x = 0; x < width; x++) {
            float xNorm = (2.0f * x) / width - 1.0f;
            ray.origin.x = xNorm;
            ray.origin.y = yNorm;

            glm::mat4 invMatrix = glm::translate(glm::mat4(1.0), -ray.origin) * invRotationMatrix;
            invMatrix = glm::translate(invMatrix, ray.origin);

            ray.origin = glm::vec3(invMatrix * glm::vec4(ray.origin.x, ray.origin.y, ray.origin.z, 1.0));

            if (rayAABBIntersect(&ray, &aabb)) {
                data[(height - y - 1) * width + x] = 0x00abffff;
            } else {
                data[(height - y - 1) * width + x] = 0xc4d3d3ffu; // background color;
            }
        }
    }

    renderOnlyFirst = true;

/*
    Entity* currentCamera = App::getInstance()->getViewport()->getCurrentCamera().get();
    CameraComponent* cameraComp = static_cast<CameraComponent*>(currentCamera->components[ComponentType::Camera].get());
    CameraSystem* cameraSystem = static_cast<CameraSystem*>(Engine::getInstance()->getSystem(SystemType::Camera).get());

    glm::mat4 inverseProjection = glm::inverse(cameraComp->projection);
    glm::mat4 inverseView = glm::inverse(cameraSystem->getView(currentCamera));
    glm::mat4 inverseViewProjection = inverseView * inverseProjection;

    // Loop on screen coordinates [0:width, height:0]
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {

            // 3D Normalised Device Coordinates [-1:1, -1:1, -1:1]
            float ndcX = (2.0f * x) / width - 1.0f;
            float ndcY = 1.0f - (2.0f * y) / height;
            float ndcZ = 1.0f;
            glm::vec3 ndsRay = glm::vec3(ndcX, ndcY, ndcZ);

            // 4D Homogeneous Clip Coordinates [-1:1, -1:1, -1:1, -1:1]
            glm::vec4 clipRay = glm::vec4(ndsRay.x, ndsRay.y, -1.0, 1.0);

            // 3D World Coordinates [-x:x, -y:y, -z:z, -w:w]
            glm::vec3 worldRay(inverseViewProjection * clipRay);
            worldRay = glm::normalize(worldRay);
        }
    }
*/
}

bool OctreeRenderer::rayAABBIntersect(OctreeRenderer::Ray* ray, AABB* aabb) {
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

#include "OctreeRenderer.h"
#include "RenderSurface.h"
#include "../Core/App.h"
#include "../ECS/Components/Components.h"
#include "../ECS/Systems/CameraSystem.h"
#include "../ECS/Engine.h"
#include "Octree.h"

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

    updateCubeTransform(transformComp->worldMatrix);

    for (int y = 0; y < height; y++) {
        float yNorm = 1.0f - (2.0f * y) / height;
        for (int x = 0; x < width; x++) {
            float xNorm = (2.0f * x) / width - 1.0f;
            if (xNorm >= cubeVerticles[0].x && xNorm <= cubeVerticles[1].x && yNorm >= cubeVerticles[0].y && yNorm <= cubeVerticles[1].y) {
                data[y * width + x] = 0x00abffff;
            } else {
                data[y * width + x] = 0xc4d3d3ffu; // background color;
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

void OctreeRenderer::updateCubeTransform(const glm::mat4& matrix) {
    cubeVerticles.clear();
    cubeVerticles.push_back(glm::vec4(-1.0, -1.0, -1.0, 1.0)); // back bottom left (min)
    cubeVerticles.push_back(glm::vec4( 1.0,  1.0,  1.0, 1.0)); // front top right (max)

    int i = 0;
    for (auto vertex : cubeVerticles) {
        cubeVerticles[i++] = matrix * vertex;
    }
}

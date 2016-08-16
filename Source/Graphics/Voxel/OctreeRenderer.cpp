#include "OctreeRenderer.h"
#include "RenderSurface.h"
#include "../Core/App.h"
#include "../ECS/Components/Components.h"
#include "../ECS/Systems/CameraSystem.h"
#include "../ECS/Engine.h"

OctreeRenderer::OctreeRenderer() {

}

void OctreeRenderer::render(const RenderSurface* renderSurface) {
    uint32* data = renderSurface->getData();
    int width = renderSurface->getWidth();
    int height = renderSurface->getHeight();

    Entity* currentCamera = App::getInstance()->getViewport()->getCurrentCamera().get();
    CameraComponent* cameraComp = static_cast<CameraComponent*>(currentCamera->components[ComponentType::Camera].get());
    CameraSystem* cameraSystem = static_cast<CameraSystem*>(Engine::getInstance()->getSystem(SystemType::Camera).get());

    glm::mat4 inverseProjection = glm::inverse(cameraComp->projection);
    glm::mat4 inverseView = glm::inverse(cameraSystem->getView(currentCamera));

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

            // 4D Eye (Camera) Coordinates [-x:x, -y:y, -z:z, -w:w]
            glm::vec4 eyeRay = inverseProjection * clipRay;

            // 3D World Coordinates [-x:x, -y:y, -z:z, -w:w]
            glm::vec3 worldRay(inverseView * eyeRay);
            worldRay = glm::normalize(worldRay);
        }
    }

//    for (int i = 0; i < count; i++) {
//        if (i < 98000) {
//            data[i] = 0x0000ffff;
//        } else {
//            data[i] = 0xff0000ff;
//        }
//    }
}

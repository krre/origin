#pragma once
#include "../ECS/Entity.h"
#include "Control.h"
#include <vector>

class Viewport : public Control {

public:
    Viewport();
    void update(float dt) override;
    void draw(float dt) override;

    void setBackgroundColor(const glm::vec4& backgroundColor);
    glm::vec4 getBackgroundColor() const { return backgroundColor; }
    void setRectangle(int x, int y, int width, int height);

    void addCamera(std::shared_ptr<Entity> camera);
    void removeCamera(std::shared_ptr<Entity> camera);
    void clearCameras();

    void setCurrentCamera(std::shared_ptr<Entity> currentCamera);
    std::shared_ptr<Entity> getCurrentCamera() const { return currentCamera; }
    // Swap last to cameras
    void switchCamera();

private:
    std::shared_ptr<Entity> currentCamera;
    std::shared_ptr<Entity> switchCameras[2];
    glm::vec4 backgroundColor;
    std::vector<std::shared_ptr<Entity>> cameras;
};

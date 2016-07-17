#pragma once
#include "../Core/Object.h"
#include "Control.h"
#include "../Graphics/Camera.h"
#include <vector>

class Viewport : public Control {

public:
    Viewport();
    void update(double dt);
    void draw(float dt) override;

    void setBackgroundColor(const glm::vec4& backgroundColor);
    void setRectangle(int x, int y, int width, int height);

    void addCamera(std::shared_ptr<Camera> camera);
    void removeCamera(std::shared_ptr<Camera> camera);
    void clearCameras();

    void setCurrentCamera(std::shared_ptr<Camera> currentCamera);
    std::shared_ptr<Camera> getCurrentCamera() const { return currentCamera; }

private:
    std::shared_ptr<Camera> currentCamera;
    glm::vec4 backgroundColor;
    glm::vec4 rectangle;
    std::vector<std::shared_ptr<Camera>> cameras;
};

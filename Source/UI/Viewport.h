#pragma once
#include "../Core/Object.h"
#include "Control.h"
#include "../Graphics/Camera.h"
#include "../Scene/Scene.h"
#include <vector>

class Viewport : public Control {

public:
    Viewport();
    void update(double dt);
    void draw();

    void setBackgroundColor(const glm::vec4& backgroundColor);
    void setRectangle(glm::vec4& rectangle);
    void setScene(std::shared_ptr<Scene> const scene) { this->scene = scene; }
    std::shared_ptr<Scene> getScene() const { return scene; }

    std::shared_ptr<Camera> getCamera() const { return camera; }

    void addCamera(std::shared_ptr<Camera> camera);
    void removeCamera(std::shared_ptr<Camera> camera);
    void clearCameras();

private:
    std::shared_ptr<Scene> scene;
    std::shared_ptr<Camera> camera;
    glm::vec4 backgroundColor;
    glm::vec4 rectangle;
    std::vector<std::shared_ptr<Camera>> cameras;
};

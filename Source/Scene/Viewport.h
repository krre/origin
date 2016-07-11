#pragma once
#include "../Core/Object.h"
#include "../Graphics/Camera.h"
#include "../Scene/Scene.h"

class Viewport : public Object {

public:
    Viewport();
    void update(double dt);
    void render();

    void setBackgroundColor(const vec4& backgroundColor);
    void setRectangle(vec4& rectangle);
    void setScene(std::shared_ptr<Scene> const scene) { this->scene = scene; }
    std::shared_ptr<Scene> getScene() const { return scene; }

    std::shared_ptr<Camera> getCamera() const { return camera; }

private:
    std::shared_ptr<Scene> scene;
    std::shared_ptr<Camera> camera;
    vec4 backgroundColor;
    vec4 rectangle;


};

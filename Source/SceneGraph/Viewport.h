#pragma once
#include "../Core/Object.h"
#include "Scene.h"
#include "../Graphics/Camera.h"
#include "../UI/View.h"

typedef list<shared_ptr<View>> ViewList;

class Viewport : public Object {

public:
    Viewport();
    void addView(shared_ptr<View> view);
    void removeView(shared_ptr<View> view);

    void setScene(shared_ptr<Scene> const scene) { this->scene = scene; }
    shared_ptr<Scene> getScene() const { return scene; }

private:
    ViewList views;
    shared_ptr<Scene> scene;
    shared_ptr<Camera> camera;
};

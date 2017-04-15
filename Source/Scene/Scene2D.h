#pragma once
#include "Scene.h"
#include <vector>

class Control;
class Layout;
class Batch2D;

class Scene2D : public Scene {

public:
    Scene2D();
    void draw(float dt) override;
    void setRoot(std::shared_ptr<Control> root);

private:
    void onWindowResize(int width, int height) override;

    std::shared_ptr<Control> root;
    std::vector<std::shared_ptr<Control>> controls;
    std::vector<std::shared_ptr<Batch2D>> batches;
};

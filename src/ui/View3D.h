#pragma once
#include "Control.h"

class Scene;

class View3D : public Control {

public:
    View3D(Control* parent = nullptr);
    View3D(Core::Rect viewport, Control* parent = nullptr);

    void setScene(const std::shared_ptr<Scene>& scene);

private:
    void updateImpl(float dt) override;
    void drawImpl() override;

    std::shared_ptr<Scene> scene;
    Core::Rect viewport;
};

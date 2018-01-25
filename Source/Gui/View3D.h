#pragma once
#include "Control.h"

namespace Origin {

class Scene;

class View3D : public Control {

public:
    View3D(const std::shared_ptr<Scene>& scene);
    void setScene(const std::shared_ptr<Scene>& scene);

private:
    std::shared_ptr<Scene> scene;
};

} // Origin

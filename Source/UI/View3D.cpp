#include "View3D.h"
#include "Scene/Scene.h"

namespace Origin {

View3D::View3D(Rect viewport, Control* parent) :
    viewport(viewport),
    Control(parent) {

}

void View3D::setScene(const std::shared_ptr<Scene>& scene) {
    this->scene = scene;
}

} // Origin

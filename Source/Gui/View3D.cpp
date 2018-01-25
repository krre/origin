#include "View3D.h"

namespace Origin {

View3D::View3D(const std::shared_ptr<Scene>& scene) : scene(scene) {

}

void View3D::setScene(const std::shared_ptr<Scene>& scene) {
    this->scene = scene;
}

} // Origin

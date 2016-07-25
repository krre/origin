#include "Scene2D.h"

void Scene2D::draw(float dt) {
    for (auto control : controls) {
        control->draw(dt);
    }
}

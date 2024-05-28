#include "View3D.h"
#include "ecs/scenes/Scene.h"
#include "ecs/EntityManager.h"
#include "graphics/render/SceneRenderer.h"

View3D::View3D(Control* parent) : Control(parent) {

}

View3D::View3D(Core::Rect viewport, Control* parent) :
    viewport(viewport),
    Control(parent) {

}

void View3D::setScene(const std::shared_ptr<Scene>& scene) {
    this->scene = scene;
}

void View3D::updateImpl(float dt) {
    if (scene) {
        EntityManager::get()->update(scene.get(), dt);
    }
}

void View3D::drawImpl() {
    if (scene) {
        SceneRenderer::get()->addView(this);
    }
}

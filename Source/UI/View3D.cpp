#include "View3D.h"
#include "ECS/Scenes/Scene.h"
#include "ECS/EntityManager.h"
#include "Graphics/Render/SceneRenderer.h"

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

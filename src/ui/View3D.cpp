#include "View3D.h"
#include "ecs/scenes/Scene.h"
#include "ecs/EntityManager.h"
#include "graphics/render/SceneRenderer.h"

View3D::View3D(Control* parent) : Control(parent) {

}

View3D::View3D(const Core::Rect& viewport, Control* parent) : Control(parent), m_viewport(viewport) {

}

void View3D::setScene(const std::shared_ptr<Scene>& scene) {
    m_scene = scene;
}

void View3D::updateImpl(float dt) {
    if (m_scene) {
        EntityManager::get()->update(m_scene.get(), dt);
    }
}

void View3D::drawImpl() {
    if (m_scene) {
        SceneRenderer::get()->addView(this);
    }
}

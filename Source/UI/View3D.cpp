#include "View3D.h"
#include "Base/Game.h"
#include "ECS/Scenes/Scene.h"
#include "Graphics/Render/RenderManager.h"
#include "Graphics/Render/SceneRenderer.h"

namespace Origin {

View3D::View3D(Control* parent) : Control(parent) {

}

View3D::View3D(Rect viewport, Control* parent) :
    viewport(viewport),
    Control(parent) {

}

void View3D::setScene(const std::shared_ptr<Scene>& scene) {
    this->scene = scene;
}

void View3D::drawImpl() {
    if (scene) {
        RenderManager::get()->getSceneRenderer()->addScene(scene.get());
    }
}

} // Origin

#include "SceneRenderer.h"

namespace Origin {

SceneRenderer::SceneRenderer(Object* parent) : Object(parent) {

}

SceneRenderer::~SceneRenderer() {

}

void SceneRenderer::addScene(Scene* scene) {
    scenes.push_back(scene);
}

void SceneRenderer::drawScenes() {
    for (Scene* scene : scenes) {

    }

    scenes.clear();
}

} // Origin

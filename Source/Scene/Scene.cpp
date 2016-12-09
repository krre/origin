#include "Scene.h"
#include "../Event/Event.h"

Scene::Scene() {
    Event::get()->windowResize.connect<Scene, &Scene::onWindowResize>(this);
}


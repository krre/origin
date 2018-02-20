#include "Scene.h"
#include "Octree/Octree.h"

namespace Origin {

Scene::Scene(Object* parent) : Object(parent) {
    rootOctree = new Object(this);
}

Scene::~Scene() {
}

void Scene::addOctree(Octree* octree) {
    rootOctree->addChild(octree);
}

} // Origin

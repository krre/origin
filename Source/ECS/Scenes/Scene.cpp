#include "Scene.h"
#include "ECS/Entity.h"

namespace Origin {

Scene::Scene(Object* parent) : Object(parent) {

}

Scene::~Scene() {
}

void Scene::setRootEntity(Entity* entity) {
    entity->setParent(this);
    this->rootEntity = entity;
}

} // Origin

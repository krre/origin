#include "Scene.h"
#include "ECS/Entity.h"

Scene::Scene(Object* parent) : Object(parent) {

}

Scene::~Scene() {
}

void Scene::setRootEntity(Entity* entity) {
    entity->setParent(this);
    this->rootEntity = entity;
}

#include "Scene.h"
#include "ecs/Entity.h"

Scene::Scene(Object* parent) : Object(parent) {

}

Scene::~Scene() {
}

void Scene::setRootEntity(Entity* entity) {
    entity->setParent(this);
    this->m_rootEntity = entity;
}

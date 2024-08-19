#include "Scene.h"
#include "ecs/Entity.h"

Scene::Scene(Object* parent) : Object(parent) {

}

void Scene::setRootEntity(Entity* entity) {
    entity->setParent(this);
    m_rootEntity = entity;
}

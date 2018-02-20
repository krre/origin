#include "Scene.h"
#include "ECS/Entity.h"

namespace Origin {

Scene::Scene(Object* parent) : Object(parent) {

}

Scene::~Scene() {
}

void Scene::setEntity(Entity* entity) {
    entity->setParent(this);
    this->entity = entity;
}

} // Origin

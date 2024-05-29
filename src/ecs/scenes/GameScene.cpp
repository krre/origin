#include "GameScene.h"
#include "ecs/Entity.h"
#include "ecs/components/Components.h"
#include <octree/Octree.h>

GameScene::GameScene(Object* parent) : Scene(parent) {
    Entity* entity = new Entity;

    std::shared_ptr<OctreeComponent> octreeComponent = std::make_shared<OctreeComponent>();
    octreeComponent->octree = std::make_shared<Octree::Octree>();
    entity->addComponent(octreeComponent);
    entity->addComponent(std::make_shared<TransformComponent>());
    setRootEntity(entity);
}

GameScene::~GameScene() {

}

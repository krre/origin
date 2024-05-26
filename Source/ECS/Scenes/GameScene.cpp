#include "GameScene.h"
#include "ECS/Entity.h"
#include "Octree/Octree.h"
#include "ECS/Components/Components.h"

namespace Origin {

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

} // Origin

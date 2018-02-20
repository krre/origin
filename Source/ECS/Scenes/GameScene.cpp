#include "GameScene.h"
#include "ECS/Entity.h"

namespace Origin {

GameScene::GameScene(Object* parent) : Scene(parent) {
    Entity* entity = new Entity;
    setEntity(entity);
}

GameScene::~GameScene() {

}

} // Origin

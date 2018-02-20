#include "GameScene.h"
#include "Octree/Octree.h"

namespace Origin {

GameScene::GameScene(Object* parent) : Scene(parent) {
    addOctree(new Octree);
}

GameScene::~GameScene() {

}

} // Origin

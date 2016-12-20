#include "WorldScene.h"
#include "../ECS/Engine.h"
#include "../ECS/System.h"
#include "../ECS/EntityBuilder.h"
#include "../ECS/Components/Components.h"
#include "../ECS/Systems/Systems.h"
#include "../Resource/ResourceManager.h"


WorldScene::WorldScene() {

}

void WorldScene::draw(float dt) {

}

void WorldScene::update(float dt) {

}

void WorldScene::create() {
    TransformSystem* transformSystem = static_cast<TransformSystem*>(Engine::get()->getSystem(SystemType::Transform).get());
    OctreeSystem* octreeSystem = static_cast<OctreeSystem*>(Engine::get()->getSystem(SystemType::Octree).get());
    PhisicsSystem* phisicsSystem = static_cast<PhisicsSystem*>(Engine::get()->getSystem(SystemType::Phisics).get());

    // Free camera
    std::shared_ptr<Entity> freeCamera = EntityBuilder::freeCamera();
    transformSystem->lookAt(freeCamera.get(), glm::vec3(3.0f, 0.0f, 0.0f), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
    transformSystem->translate(freeCamera.get(), glm::vec3(2.0f, 1.0f, 3.0f));
//    App::get()->getViewport()->setCurrentCamera(freeCamera);
    Engine::get()->addEntity(freeCamera);

    // Avatar
    auto avatar = EntityBuilder::avatar();
    Engine::get()->addEntity(avatar);

    std::shared_ptr<Entity> avatarCamera = EntityBuilder::camera();
//    App::get()->getViewport()->setCurrentCamera(avatarCamera);
    transformSystem->translate(avatarCamera.get(), glm::vec3(0.0f, 0.0f, 2.0f));
//    transformSystem->setPitch(avatarCamera.get(), -15.0);
//    NodeSystem* nodeSystem = static_cast<NodeSystem*>(Engine::get()->getSystem(SystemType::Node).get());
//    nodeSystem->addChild(avatar->getId(), avatarCamera->getId());
    characterId = avatarCamera->getId();

    std::shared_ptr<PhisicsComponent> phisicsComponent = std::make_shared<PhisicsComponent>();
    phisicsComponent->mass = 1.0;
    phisicsComponent->collisionShape.reset(new btCapsuleShape(0.5, 1.75));
    Engine::get()->addComponent(avatarCamera.get(), phisicsComponent);
    phisicsSystem->createMotionState(avatarCamera.get());
    phisicsSystem->createRigidBody(avatarCamera.get());
    phisicsComponent->rigidBody->setAngularFactor(btVector3(0, 0, 0));
    phisicsSystem->addRigidBody(avatarCamera.get());

    Engine::get()->addEntity(avatarCamera);

    octreeSystem->getGpuMemoryManager()->beginBatch();

    // Ground
    std::shared_ptr<Entity> ground = EntityBuilder::geometry();
    transformSystem->setScale(ground.get(), 5);
    transformSystem->setPosition(ground.get(), glm::vec3(0.0, 1.0, 0.0));
    OctreeComponent* groundOctree = static_cast<OctreeComponent*>(ground->components[ComponentType::Octree].get());
    groundOctree->data = ResourceManager::get()->getResource<Octree>("GroundOctree")->data();
    Engine::get()->addEntity(ground);
    octreeSystem->getGpuMemoryManager()->addEntity(ground.get());

    // Trees
    std::shared_ptr<Entity> tree1 = EntityBuilder::geometry();
    transformSystem->setScale(tree1.get(), 1.2);
    transformSystem->setPosition(tree1.get(), glm::vec3(1.0, 0.15, 0.0));

    phisicsSystem->createCollisionShape(tree1.get());
    phisicsSystem->createMotionState(tree1.get());
    phisicsSystem->createRigidBody(tree1.get());
    phisicsSystem->addRigidBody(tree1.get());

    OctreeComponent* tree1Octree = static_cast<OctreeComponent*>(tree1->components[ComponentType::Octree].get());
    tree1Octree->data = ResourceManager::get()->getResource<Octree>("TreeOctree")->data();
    Engine::get()->addEntity(tree1);
    octreeSystem->getGpuMemoryManager()->addEntity(tree1.get());

    std::shared_ptr<Entity> tree2 = EntityBuilder::geometry();
    transformSystem->setScale(tree2.get(), 0.9);
    transformSystem->setPosition(tree2.get(), glm::vec3(-0.7, 0.15, 1.2));

    phisicsSystem->createCollisionShape(tree2.get());
    phisicsSystem->createMotionState(tree2.get());
    phisicsSystem->createRigidBody(tree2.get());
    phisicsSystem->addRigidBody(tree2.get());

    OctreeComponent* tree2Octree = static_cast<OctreeComponent*>(tree2->components[ComponentType::Octree].get());
    tree2Octree->data = ResourceManager::get()->getResource<Octree>("TreeOctree")->data();
    Engine::get()->addEntity(tree2);
    octreeSystem->getGpuMemoryManager()->addEntity(tree2.get());

    std::shared_ptr<Entity> tree3 = EntityBuilder::geometry();
    transformSystem->setScale(tree3.get(), 1.1);
    transformSystem->setPosition(tree3.get(), glm::vec3(-0.3, 0.15, -1.8));

    phisicsSystem->createCollisionShape(tree3.get());
    phisicsSystem->createMotionState(tree3.get());
    phisicsSystem->createRigidBody(tree3.get());
    phisicsSystem->addRigidBody(tree3.get());

    OctreeComponent* tree3Octree = static_cast<OctreeComponent*>(tree3->components[ComponentType::Octree].get());
    tree3Octree->data = ResourceManager::get()->getResource<Octree>("TreeOctree")->data();
    Engine::get()->addEntity(tree3);
    octreeSystem->getGpuMemoryManager()->addEntity(tree3.get());

    // Chamomiles
    std::shared_ptr<Entity> chamomile1 = EntityBuilder::geometry();
    transformSystem->setScale(chamomile1.get(), 0.04);
    transformSystem->setPosition(chamomile1.get(), glm::vec3(0.2, -0.22, 0.2));
    OctreeComponent* chamomile1Octree = static_cast<OctreeComponent*>(chamomile1->components[ComponentType::Octree].get());
    chamomile1Octree->data = ResourceManager::get()->getResource<Octree>("ChamomileOctree")->data();
    Engine::get()->addEntity(chamomile1);
    octreeSystem->getGpuMemoryManager()->addEntity(chamomile1.get());

    std::shared_ptr<Entity> chamomile2 = EntityBuilder::geometry();
    transformSystem->setScale(chamomile2.get(), 0.04);
    transformSystem->setPosition(chamomile2.get(), glm::vec3(-0.3, -0.22, 1.3));
    OctreeComponent* chamomile2Octree = static_cast<OctreeComponent*>(chamomile2->components[ComponentType::Octree].get());
    chamomile2Octree->data = ResourceManager::get()->getResource<Octree>("ChamomileOctree")->data();
    Engine::get()->addEntity(chamomile2);
    octreeSystem->getGpuMemoryManager()->addEntity(chamomile2.get());

    std::shared_ptr<Entity> chamomile3 = EntityBuilder::geometry();
    transformSystem->setScale(chamomile3.get(), 0.04);
    transformSystem->setPosition(chamomile3.get(), glm::vec3(0.4, -0.22, 1.0));
    OctreeComponent* chamomile3Octree = static_cast<OctreeComponent*>(chamomile3->components[ComponentType::Octree].get());
    chamomile3Octree->data = ResourceManager::get()->getResource<Octree>("ChamomileOctree")->data();
    Engine::get()->addEntity(chamomile3);
    octreeSystem->getGpuMemoryManager()->addEntity(chamomile3.get());

    octreeSystem->getGpuMemoryManager()->endBatch();
    octreeSystem->getGpuMemoryManager()->updateRenderList();

    // Light
    std::shared_ptr<Entity> light = EntityBuilder::light();
    transformSystem->translate(light.get(), glm::vec3(1.5, 2.5, 1.0));
    Engine::get()->addEntity(light);

    Event::get()->keyPressed.connect<WorldScene, &WorldScene::onKeyPressed>(this);
}

void WorldScene::onKeyPressed(const SDL_KeyboardEvent& event) {

}

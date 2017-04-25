#include "WorldScene.h"
#include <Origin.h>
#include "Core/Game.h"
#include "Debug/Console.h"
#include "ECS/EntityManager.h"
#include "ECS/System.h"
#include "ECS/EntityBuilder.h"
#include "ECS/Components/Components.h"
#include "ECS/Systems/Systems.h"
#include "Resource/ResourceManager.h"
#include "Scene/SceneManager.h"
#include "UI/Dialog/PauseDialog.h"
#include "Event/Input.h"
#include "Graphics/Vulkan/Instance.h"
#include "Graphics/Vulkan/Swapchain.h"
#include "Graphics/Vulkan/Framebuffer.h"
#include "Graphics/Vulkan/Pipeline/GraphicsPipeline.h"
#include "Graphics/Buffer/VertexBuffer.h"
#include "Graphics/Buffer/IndexBuffer.h"
#include "Resource/ShaderResource.h"
#include "Resource/ResourceManager.h"
#include "Graphics/Vulkan/Command/CommandBuffer.h"
#include "Graphics/Vulkan/Command/CommandBuffers.h"
#include "Graphics/Vulkan/Descriptor/DescriptorSets.h"
#include "Graphics/Vulkan/Queue/SubmitQueue.h"

WorldScene::WorldScene() {
    new EntityManager;
    console = std::make_shared<Console>();
    Game::get()->setWorldScene(this);
}

WorldScene::~WorldScene() {
    if (Game::exists()) {
        Game::get()->setWorldScene(nullptr);
    }
    EntityManager::get()->release();
}

void WorldScene::init() {
    shaderProgram.addShader("Shader/Voxel.vert.spv");
    shaderProgram.addShader("Shader/Voxel.frag.spv");

    shaderProgram.linkUniform("ubo", sizeof(ubo), &ubo);
    shaderProgram.linkUniform("octree", MEMORY_SIZE);
    shaderProgram.linkUniform("renderList", MAX_OCTREE_COUNT * sizeof(uint32_t));
    shaderProgram.linkUniform("pickResult", sizeof(pickResult), &pickResult);
    shaderProgram.linkUniform("debugOut", sizeof(debugOut), &debugOut);

    int binding = shaderProgram.createVertexInputBindingDescription(sizeof(glm::vec2));
    shaderProgram.linkInput("position", binding);

    vertexBuffer = std::unique_ptr<VertexBuffer>(new VertexBuffer(plane.getVerticesSize()));
    vertexBuffer->write(plane.getVertices().data(), plane.getVerticesSize());

    indexBuffer = std::unique_ptr<IndexBuffer>(new IndexBuffer(plane.getIndicesSize()));
    indexBuffer->write(plane.getIndices().data(), plane.getIndicesSize());

    shaderProgram.createPipeline();

    buildCommandBuffers();

    create();
}

void WorldScene::draw(float dt) {
    queue->submit();

//    debugOutBuffer->read(0, sizeof(DebugOut), &debugOut);
//    PRINT(glm::to_string(debugOut.debugVec))
//    PRINT(debugOut.debugInt)
}

void WorldScene::update(float dt) {
    EntityManager::get()->update(dt);

    int width = App::get()->getWidth();
    int height = App::get()->getHeight();

    OctreeSystem* octreeSystem = static_cast<OctreeSystem*>(EntityManager::get()->getSystem(SystemType::Octree).get());
    Entity* currentCamera = getCurrentCamera().get();
    CameraComponent* cameraComp = static_cast<CameraComponent*>(currentCamera->components[ComponentType::Camera].get());
    TransformComponent* cameraTransform = static_cast<TransformComponent*>(currentCamera->components[ComponentType::Transform].get());

    TransformComponent* octreeTransform;

    TransformComponent* lightTransform;
    ubo.lightColor = glm::vec4(0.0);
    ubo.lightPos = glm::vec4(0.0);

    // TODO: Replace by family
    for (auto& entity : EntityManager::get()->getEntities()) {
        OctreeComponent* octreeComp = static_cast<OctreeComponent*>(entity.second->components[ComponentType::Octree].get());
        if (octreeComp) {
            octreeTransform = static_cast<TransformComponent*>(entity.second->components[ComponentType::Transform].get());
        }

        LightComponent* lightComp = static_cast<LightComponent*>(entity.second->components[ComponentType::Light].get());
        if (lightComp) {
            lightTransform = static_cast<TransformComponent*>(entity.second->components[ComponentType::Transform].get());
            ubo.lightColor = glm::vec4(lightComp->color, 1.0);
            ubo.lightPos = lightTransform->objectToWorld[3];
        }
    }

    ubo.transformCount = 0;

    for (auto& imap : octreeSystem->getGpuMemoryManager()->getOctreeOffsets()) {
        std::vector<glm::vec4> transform;
        Entity* entity = EntityManager::get()->getEntity(imap.first).get();
        TransformComponent* octreeTransform = static_cast<TransformComponent*>(entity->components[ComponentType::Transform].get());
        transform.push_back(octreeTransform->objectToWorld[0]);
        transform.push_back(octreeTransform->objectToWorld[1]);
        transform.push_back(octreeTransform->objectToWorld[2]);
        transform.push_back(octreeTransform->objectToWorld[3]);

        glm::mat4 cameraToOctree = octreeTransform->worldToObject * cameraTransform->objectToWorld;
        transform.push_back(cameraToOctree[3]);

        glm::vec4 up = cameraToOctree * cameraComp->up;
        glm::vec4 look = cameraToOctree * cameraComp->look;
        glm::vec4 right = cameraToOctree * cameraComp->right;

        // Ray calculation is based on Johns Hopkins presentation:
        // http://www.cs.jhu.edu/~cohen/RendTech99/Lectures/Ray_Casting.bw.pdf
        glm::vec4 h0 = look - up * glm::tan(cameraComp->fov); // min height vector
        glm::vec4 h1 = look + up * glm::tan(cameraComp->fov); // max height vector
        glm::vec4 stepH = (h1 - h0) / height;
        h0 += stepH / 2;

        glm::vec4 w0 = look - right * glm::tan(cameraComp->fov) * width / height; // min width vector
        glm::vec4 w1 = look + right * glm::tan(cameraComp->fov) * width / height; // max width vector
        glm::vec4 stepW = (w1 - w0) / width;
        w0 += stepW / 2;

        glm::vec4 startCornerPos = w0 + h0;

        transform.push_back(startCornerPos);
        transform.push_back(stepW);
        transform.push_back(stepH);

        octreeSystem->getGpuMemoryManager()->updateEntityTransform(entity, transform, shaderProgram.getUniformBuffer("octree"));

        if (!ubo.transformCount) {
            ubo.transformCount = transform.size();
        }
    }

    ubo.frameWidth = width;
    ubo.frameHeight = height;
    ubo.lod = glm::tan(LOD_PIXEL_LIMIT * cameraComp->fov / height);
    shaderProgram.writeUniform("ubo");
}

void WorldScene::create() {
    TransformSystem* transformSystem = static_cast<TransformSystem*>(EntityManager::get()->getSystem(SystemType::Transform).get());
    OctreeSystem* octreeSystem = static_cast<OctreeSystem*>(EntityManager::get()->getSystem(SystemType::Octree).get());
    PhysicsSystem* physicsSystem = static_cast<PhysicsSystem*>(EntityManager::get()->getSystem(SystemType::Physics).get());

    // Free camera
    std::shared_ptr<Entity> freeCamera = EntityBuilder::freeCamera();
    transformSystem->lookAt(freeCamera.get(), glm::vec3(3.0f, 0.0f, 0.0f), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
    transformSystem->translate(freeCamera.get(), glm::vec3(2.0f, 1.0f, 3.0f));
    setCurrentCamera(freeCamera);
    EntityManager::get()->addEntity(freeCamera);

    // Avatar
    auto avatar = EntityBuilder::avatar();
    EntityManager::get()->addEntity(avatar);

    std::shared_ptr<Entity> avatarCamera = EntityBuilder::camera();
    setCurrentCamera(avatarCamera);
    transformSystem->translate(avatarCamera.get(), glm::vec3(0.0f, 0.0f, 2.0f));
    transformSystem->setPitch(avatarCamera.get(), -15.0);
//    NodeSystem* nodeSystem = static_cast<NodeSystem*>(EntityManager::get()->getSystem(SystemType::Node).get());
//    nodeSystem->addChild(avatar->getId(), avatarCamera->getId());
    characterId = avatarCamera->getId();

    std::shared_ptr<PhysicsComponent> physicsComponent = std::make_shared<PhysicsComponent>();
    physicsComponent->mass = 1.0;
    physicsComponent->collisionShape.reset(new btCapsuleShape(0.5, 1.75));
    EntityManager::get()->addComponent(avatarCamera.get(), physicsComponent);
    physicsSystem->createMotionState(avatarCamera.get());
    physicsSystem->createRigidBody(avatarCamera.get());
    physicsComponent->rigidBody->setAngularFactor(btVector3(0, 0, 0));
    physicsSystem->addRigidBody(avatarCamera.get());

    EntityManager::get()->addEntity(avatarCamera);

    Vulkan::Buffer* octreeBuffer = shaderProgram.getUniformBuffer("octree");

    // Ground
    std::shared_ptr<Entity> ground = EntityBuilder::geometry();
    transformSystem->setScale(ground.get(), 5);
    transformSystem->setPosition(ground.get(), glm::vec3(0.0, 1.0, 0.0));
    OctreeComponent* groundOctree = static_cast<OctreeComponent*>(ground->components[ComponentType::Octree].get());
    groundOctree->data = ResourceManager::get()->load<Octree>("Octree/Ground.json")->data();
    EntityManager::get()->addEntity(ground);
    octreeSystem->getGpuMemoryManager()->addEntity(ground.get(), octreeBuffer);

    // Trees
    std::shared_ptr<Entity> tree1 = EntityBuilder::geometry();
    transformSystem->setScale(tree1.get(), 1.2);
    transformSystem->setPosition(tree1.get(), glm::vec3(1.0, 0.15, 0.0));

    physicsSystem->createCollisionShape(tree1.get());
    physicsSystem->createMotionState(tree1.get());
    physicsSystem->createRigidBody(tree1.get());
    physicsSystem->addRigidBody(tree1.get());

    OctreeComponent* tree1Octree = static_cast<OctreeComponent*>(tree1->components[ComponentType::Octree].get());
    tree1Octree->data = ResourceManager::get()->load<Octree>("Octree/Tree.json")->data();
    EntityManager::get()->addEntity(tree1);
    octreeSystem->getGpuMemoryManager()->addEntity(tree1.get(), octreeBuffer);

    std::shared_ptr<Entity> tree2 = EntityBuilder::geometry();
    transformSystem->setScale(tree2.get(), 0.9);
    transformSystem->setPosition(tree2.get(), glm::vec3(-0.7, 0.15, 1.2));

    physicsSystem->createCollisionShape(tree2.get());
    physicsSystem->createMotionState(tree2.get());
    physicsSystem->createRigidBody(tree2.get());
    physicsSystem->addRigidBody(tree2.get());

    OctreeComponent* tree2Octree = static_cast<OctreeComponent*>(tree2->components[ComponentType::Octree].get());
    tree2Octree->data = ResourceManager::get()->load<Octree>("Octree/Tree.json")->data();
    EntityManager::get()->addEntity(tree2);
    octreeSystem->getGpuMemoryManager()->addEntity(tree2.get(), octreeBuffer);

    std::shared_ptr<Entity> tree3 = EntityBuilder::geometry();
    transformSystem->setScale(tree3.get(), 1.1);
    transformSystem->setPosition(tree3.get(), glm::vec3(-0.3, 0.15, -1.8));

    physicsSystem->createCollisionShape(tree3.get());
    physicsSystem->createMotionState(tree3.get());
    physicsSystem->createRigidBody(tree3.get());
    physicsSystem->addRigidBody(tree3.get());

    OctreeComponent* tree3Octree = static_cast<OctreeComponent*>(tree3->components[ComponentType::Octree].get());
    tree3Octree->data = ResourceManager::get()->load<Octree>("Octree/Tree.json")->data();
    EntityManager::get()->addEntity(tree3);
    octreeSystem->getGpuMemoryManager()->addEntity(tree3.get(), octreeBuffer);

    // Chamomiles
    std::shared_ptr<Entity> chamomile1 = EntityBuilder::geometry();
    transformSystem->setScale(chamomile1.get(), 0.04);
    transformSystem->setPosition(chamomile1.get(), glm::vec3(0.2, -0.22, 0.2));
    OctreeComponent* chamomile1Octree = static_cast<OctreeComponent*>(chamomile1->components[ComponentType::Octree].get());
    chamomile1Octree->data = ResourceManager::get()->load<Octree>("Octree/Chamomile.json")->data();
    EntityManager::get()->addEntity(chamomile1);
    octreeSystem->getGpuMemoryManager()->addEntity(chamomile1.get(), octreeBuffer);

    std::shared_ptr<Entity> chamomile2 = EntityBuilder::geometry();
    transformSystem->setScale(chamomile2.get(), 0.04);
    transformSystem->setPosition(chamomile2.get(), glm::vec3(-0.3, -0.22, 1.3));
    OctreeComponent* chamomile2Octree = static_cast<OctreeComponent*>(chamomile2->components[ComponentType::Octree].get());
    chamomile2Octree->data = ResourceManager::get()->load<Octree>("Octree/Chamomile.json")->data();;
    EntityManager::get()->addEntity(chamomile2);
    octreeSystem->getGpuMemoryManager()->addEntity(chamomile2.get(), octreeBuffer);

    std::shared_ptr<Entity> chamomile3 = EntityBuilder::geometry();
    transformSystem->setScale(chamomile3.get(), 0.04);
    transformSystem->setPosition(chamomile3.get(), glm::vec3(0.4, -0.22, 1.0));
    OctreeComponent* chamomile3Octree = static_cast<OctreeComponent*>(chamomile3->components[ComponentType::Octree].get());
    chamomile3Octree->data = ResourceManager::get()->load<Octree>("Octree/Chamomile.json")->data();;
    EntityManager::get()->addEntity(chamomile3);
    octreeSystem->getGpuMemoryManager()->addEntity(chamomile3.get(), octreeBuffer);

    octreeSystem->getGpuMemoryManager()->updateRenderList(shaderProgram.getUniformBuffer("renderList"));

    // Light
    std::shared_ptr<Entity> light = EntityBuilder::light();
    transformSystem->translate(light.get(), glm::vec3(1.5, 2.5, 1.0));
    EntityManager::get()->addEntity(light);
}

void WorldScene::writeCommands(Vulkan::CommandBuffer* commandBuffer) {
    VkExtent2D extent = Vulkan::Instance::get()->getSurface()->getCurrentExtent();

    VkViewport viewport = {};
    viewport.width = extent.width;
    viewport.height = extent.height;
    viewport.maxDepth = 1.0;

    VkRect2D scissor = {};
    scissor.offset = { 0, 0 };
    scissor.extent = extent;

    VkRenderPassBeginInfo* renderPassBeginInfo = &Vulkan::Instance::get()->getSurface()->getSwapchain()->getRenderPass()->beginInfo;
    commandBuffer->beginRenderPass(renderPassBeginInfo);

    commandBuffer->bindPipeline(shaderProgram.getGraphicsPipeline());

    commandBuffer->addViewport(viewport);
    commandBuffer->setViewport(0);

    commandBuffer->addScissor(scissor);
    commandBuffer->setScissor(0);

    commandBuffer->addVertexBuffer(vertexBuffer->getHandle());
    commandBuffer->bindVertexBuffers();
    commandBuffer->bindIndexBuffer(indexBuffer->getHandle());

    for (int i = 0; i < shaderProgram.getDescriptorSets()->getCount(); i++) {
        commandBuffer->addDescriptorSet(shaderProgram.getDescriptorSets()->at(i));
    }

    commandBuffer->bindDescriptorSets(shaderProgram.getGraphicsPipeline()->getBindPoint(), shaderProgram.getPipelineLayout()->getHandle());
    commandBuffer->drawIndexed(plane.getIndices().size(), 1, 0, 0, 0);

    commandBuffer->endRenderPass();
}

void WorldScene::pause() {
    Scene::pause();
    MovementControllerSystem* movementControllerSystem = static_cast<MovementControllerSystem*>(EntityManager::get()->getSystem(SystemType::MovementController).get());
    movementControllerSystem->setActive(false);
    SDL_SetRelativeMouseMode(SDL_FALSE);
}

void WorldScene::resume() {
    Scene::resume();
    MovementControllerSystem* movementControllerSystem = static_cast<MovementControllerSystem*>(EntityManager::get()->getSystem(SystemType::MovementController).get());
    movementControllerSystem->setActive(true);
    SDL_SetRelativeMouseMode(SDL_TRUE);
}

void WorldScene::setSeed(uint64_t seed) {
    this->seed = seed;
}

void WorldScene::onKeyPressed(const SDL_KeyboardEvent& event) {
    switch (event.keysym.sym) {
    case SDLK_ESCAPE:
        SceneManager::get()->pushScene(std::make_shared<PauseDialog>());
        Input::get()->isKeyAccepted = true;
        break;

#ifdef CONSOLE_ENABLE
    case SDLK_SLASH:
//        MovementControllerSystem* movementControllerSystem = static_cast<MovementControllerSystem*>(EntityManager::get()->getSystem(SystemType::MovementController).get());
//        movementControllerSystem->setActive(false);
//        Console::get()->setVisible(true);
        SceneManager::get()->pushScene(console);
        break;
#endif

#ifdef DEVELOP_MODE
    case SDLK_KP_0:
        switchCamera();
        break;
    case SDLK_BACKQUOTE:
        SDL_SetRelativeMouseMode(SDL_GetRelativeMouseMode() == SDL_TRUE ? SDL_FALSE : SDL_TRUE);
        break;
#endif
    }
}

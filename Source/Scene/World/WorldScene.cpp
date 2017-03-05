#include "WorldScene.h"
#include <Origin.h>
#include "../../ECS/EntityManager.h"
#include "../../ECS/System.h"
#include "../../ECS/EntityBuilder.h"
#include "../../ECS/Components/Components.h"
#include "../../ECS/Systems/Systems.h"
#include "../../Resource/ResourceManager.h"
#include "../../Scene/SceneManager.h"
#include "../../Scene/PauseScene.h"
#include "../../Event/Input.h"
#include "../../Graphics/Vulkan/Manager.h"
#include "../../Resource/ShaderResource.h"
#include "../../Resource/ResourceManager.h"
#include "../../Graphics/Vulkan/Command/CommandBuffer.h"

WorldScene::WorldScene() {
    new EntityManager;
}

WorldScene::~WorldScene() {
    EntityManager::get()->release();

    delete graphicsPipeline;
    delete pipelineLayout;
    delete descriptorSets;
    delete descriptorPool;
    delete descriptorSetLayout;
    delete debugOutBuffer;
    delete pickResultBuffer;
    delete renderListBuffer;
    delete octreeBuffer;
    delete uniformFrag;
    delete indexBuffer;
    delete vertexBuffer;
}

void WorldScene::init() {
    Scene::init();

    vertexBuffer = new Vulkan::Buffer(device, plane.getVerticesSize(), Vulkan::Buffer::Type::VERTEX, Vulkan::Buffer::Destination::DEVICE);
    vertexBuffer->create();

    Vulkan::Buffer vertexStageBuffer(device, plane.getVerticesSize(), Vulkan::Buffer::Type::TRANSFER_SRC);
    vertexStageBuffer.create();
    vertexStageBuffer.write(0, plane.getVerticesSize(), plane.getVertices().data());
    vertexStageBuffer.copy(vertexBuffer->getHandle(), plane.getVerticesSize());

    indexBuffer = new Vulkan::Buffer(device, plane.getIndicesSize(), Vulkan::Buffer::Type::INDEX, Vulkan::Buffer::Destination::DEVICE);
    indexBuffer->create();

    Vulkan::Buffer indexStageBuffer(device, plane.getIndicesSize(), Vulkan::Buffer::Type::TRANSFER_SRC);
    indexStageBuffer.create();
    indexStageBuffer.write(0, plane.getIndicesSize(), plane.getIndices().data());
    indexStageBuffer.copy(indexBuffer->getHandle(), plane.getIndicesSize());

    uniformFrag = new Vulkan::Descriptor(device, VK_SHADER_STAGE_FRAGMENT_BIT, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
                                      VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 0, sizeof(UBO));

    octreeBuffer = new Vulkan::Descriptor(device, VK_SHADER_STAGE_FRAGMENT_BIT, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT,
                                      VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 1, MEMORY_SIZE);

    renderListBuffer = new Vulkan::Descriptor(device, VK_SHADER_STAGE_FRAGMENT_BIT, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT,
                                      VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 2, MAX_OCTREE_COUNT * sizeof(uint32_t));

    pickResultBuffer = new Vulkan::Descriptor(device, VK_SHADER_STAGE_FRAGMENT_BIT, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT,
                                      VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 3, sizeof(PickResult));

    debugOutBuffer = new Vulkan::Descriptor(device, VK_SHADER_STAGE_FRAGMENT_BIT, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT,
                                      VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 4, sizeof(DebugOut));

    descriptorPool = new Vulkan::DescriptorPool(device);
    descriptorPool->addPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1);
    descriptorPool->addPoolSize(VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 4);
    descriptorPool->create();

    descriptorSetLayout = new Vulkan::DescriptorSetLayout(device);

    descriptorSetLayout->addLayoutBinding(uniformFrag->setLayoutBinding);
    descriptorSetLayout->addLayoutBinding(octreeBuffer->setLayoutBinding);
    descriptorSetLayout->addLayoutBinding(renderListBuffer->setLayoutBinding);
    descriptorSetLayout->addLayoutBinding(pickResultBuffer->setLayoutBinding);
    descriptorSetLayout->addLayoutBinding(debugOutBuffer->setLayoutBinding);
    descriptorSetLayout->create();

    descriptorSets = new Vulkan::DescriptorSets(device, descriptorPool);
    descriptorSets->addDescriptorSetLayout(descriptorSetLayout);
    descriptorSets->allocate();
    descriptorSets->addDescriptor(uniformFrag);
    descriptorSets->addDescriptor(octreeBuffer);
    descriptorSets->addDescriptor(renderListBuffer);
    descriptorSets->addDescriptor(pickResultBuffer);
    descriptorSets->addDescriptor(debugOutBuffer);
    descriptorSets->writeDescriptors();

    pipelineLayout = new Vulkan::PipelineLayout(device);
    pipelineLayout->addDescriptorSetLayout(descriptorSetLayout);
    pipelineLayout->create();

    graphicsPipeline = new Vulkan::GraphicsPipeline(device);

    ShaderResource* shaderResource = ResourceManager::get()->load<ShaderResource>("Shader/Voxel.vert.spv");
    graphicsPipeline->addShaderCode(VK_SHADER_STAGE_VERTEX_BIT, (size_t)shaderResource->getSize(), (uint32_t*)shaderResource->getData());

    shaderResource = ResourceManager::get()->load<ShaderResource>("Shader/Voxel.frag.spv");
    graphicsPipeline->addShaderCode(VK_SHADER_STAGE_FRAGMENT_BIT, (size_t)shaderResource->getSize(), (uint32_t*)shaderResource->getData());

    VkVertexInputBindingDescription bindingDescription = {};
    bindingDescription.binding = 0;
    bindingDescription.stride = sizeof(glm::vec2);
    bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    graphicsPipeline->setVertexBindingDescriptions({ bindingDescription });

    VkVertexInputAttributeDescription attributeDescriptions = {};
    attributeDescriptions.binding = 0;
    attributeDescriptions.location = 0;
    attributeDescriptions.format = VK_FORMAT_R32G32_SFLOAT;
    attributeDescriptions.offset = 0;
    graphicsPipeline->setVertexAttributeDescriptions({ attributeDescriptions });

    graphicsPipeline->setExtent(Vulkan::Manager::get()->getSwapchain()->getExtent());
    graphicsPipeline->createInfo.layout = pipelineLayout->getHandle();
    graphicsPipeline->createInfo.renderPass = Vulkan::Manager::get()->getRenderPass()->getHandle();
    graphicsPipeline->create();

    buildCommandBuffers();
}

void WorldScene::draw(float dt) {
    Vulkan::Manager::get()->setCommandBuffers(commandBuffers);
    Vulkan::Manager::get()->submit();

//    debugOutBuffer->read(0, sizeof(DebugOut), &debugOut);
//    PRINT(glm::to_string(debugOut.debugVec))
//    PRINT(debugOut.debugInt)
}

void WorldScene::update(float dt) {
    EntityManager::get()->update(dt);

    int width = App::get()->getWidth();
    int height = App::get()->getHeight();

    OctreeSystem* octreeSystem = static_cast<OctreeSystem*>(EntityManager::get()->getSystem(SystemType::Octree).get());
    Entity* currentCamera = viewport.getCurrentCamera().get();
    CameraComponent* cameraComp = static_cast<CameraComponent*>(currentCamera->components[ComponentType::Camera].get());
    TransformComponent* cameraTransform = static_cast<TransformComponent*>(currentCamera->components[ComponentType::Transform].get());

    TransformComponent* octreeTransform;

    TransformComponent* lightTransform;
    ubo.lightColor = glm::vec4(0.0);
    ubo.lightPos = glm::vec4(0.0);

    // TODO: Replace by family
    for (auto entity : EntityManager::get()->getEntities()) {
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

    for (auto imap: octreeSystem->getGpuMemoryManager()->getOctreeOffsets()) {
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

        octreeSystem->getGpuMemoryManager()->updateEntityTransform(entity, transform, octreeBuffer);

        if (!ubo.transformCount) {
            ubo.transformCount = transform.size();
        }
    }

    ubo.frameWidth = width;
    ubo.frameHeight = height;
    ubo.lod = glm::tan(LOD_PIXEL_LIMIT * cameraComp->fov / height);
    uniformFrag->write(0, sizeof(UBO), &ubo);
}

void WorldScene::create() {
    TransformSystem* transformSystem = static_cast<TransformSystem*>(EntityManager::get()->getSystem(SystemType::Transform).get());
    OctreeSystem* octreeSystem = static_cast<OctreeSystem*>(EntityManager::get()->getSystem(SystemType::Octree).get());
    PhisicsSystem* phisicsSystem = static_cast<PhisicsSystem*>(EntityManager::get()->getSystem(SystemType::Phisics).get());

    // Free camera
    std::shared_ptr<Entity> freeCamera = EntityBuilder::freeCamera();
    transformSystem->lookAt(freeCamera.get(), glm::vec3(3.0f, 0.0f, 0.0f), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
    transformSystem->translate(freeCamera.get(), glm::vec3(2.0f, 1.0f, 3.0f));
    viewport.setCurrentCamera(freeCamera);
    EntityManager::get()->addEntity(freeCamera);

    // Avatar
    auto avatar = EntityBuilder::avatar();
    EntityManager::get()->addEntity(avatar);

    std::shared_ptr<Entity> avatarCamera = EntityBuilder::camera();
    viewport.setCurrentCamera(avatarCamera);
    transformSystem->translate(avatarCamera.get(), glm::vec3(0.0f, 0.0f, 2.0f));
    transformSystem->setPitch(avatarCamera.get(), -15.0);
//    NodeSystem* nodeSystem = static_cast<NodeSystem*>(EntityManager::get()->getSystem(SystemType::Node).get());
//    nodeSystem->addChild(avatar->getId(), avatarCamera->getId());
    characterId = avatarCamera->getId();

    std::shared_ptr<PhisicsComponent> phisicsComponent = std::make_shared<PhisicsComponent>();
    phisicsComponent->mass = 1.0;
    phisicsComponent->collisionShape.reset(new btCapsuleShape(0.5, 1.75));
    EntityManager::get()->addComponent(avatarCamera.get(), phisicsComponent);
    phisicsSystem->createMotionState(avatarCamera.get());
    phisicsSystem->createRigidBody(avatarCamera.get());
    phisicsComponent->rigidBody->setAngularFactor(btVector3(0, 0, 0));
    phisicsSystem->addRigidBody(avatarCamera.get());

    EntityManager::get()->addEntity(avatarCamera);

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

    phisicsSystem->createCollisionShape(tree1.get());
    phisicsSystem->createMotionState(tree1.get());
    phisicsSystem->createRigidBody(tree1.get());
    phisicsSystem->addRigidBody(tree1.get());

    OctreeComponent* tree1Octree = static_cast<OctreeComponent*>(tree1->components[ComponentType::Octree].get());
    tree1Octree->data = ResourceManager::get()->load<Octree>("Octree/Tree.json")->data();
    EntityManager::get()->addEntity(tree1);
    octreeSystem->getGpuMemoryManager()->addEntity(tree1.get(), octreeBuffer);

    std::shared_ptr<Entity> tree2 = EntityBuilder::geometry();
    transformSystem->setScale(tree2.get(), 0.9);
    transformSystem->setPosition(tree2.get(), glm::vec3(-0.7, 0.15, 1.2));

    phisicsSystem->createCollisionShape(tree2.get());
    phisicsSystem->createMotionState(tree2.get());
    phisicsSystem->createRigidBody(tree2.get());
    phisicsSystem->addRigidBody(tree2.get());

    OctreeComponent* tree2Octree = static_cast<OctreeComponent*>(tree2->components[ComponentType::Octree].get());
    tree2Octree->data = ResourceManager::get()->load<Octree>("Octree/Tree.json")->data();
    EntityManager::get()->addEntity(tree2);
    octreeSystem->getGpuMemoryManager()->addEntity(tree2.get(), octreeBuffer);

    std::shared_ptr<Entity> tree3 = EntityBuilder::geometry();
    transformSystem->setScale(tree3.get(), 1.1);
    transformSystem->setPosition(tree3.get(), glm::vec3(-0.3, 0.15, -1.8));

    phisicsSystem->createCollisionShape(tree3.get());
    phisicsSystem->createMotionState(tree3.get());
    phisicsSystem->createRigidBody(tree3.get());
    phisicsSystem->addRigidBody(tree3.get());

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

    octreeSystem->getGpuMemoryManager()->updateRenderList(renderListBuffer);

    // Light
    std::shared_ptr<Entity> light = EntityBuilder::light();
    transformSystem->translate(light.get(), glm::vec3(1.5, 2.5, 1.0));
    EntityManager::get()->addEntity(light);
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
    if (event.keysym.sym == SDLK_ESCAPE) {
        SceneManager::get()->pushScene(std::make_shared<PauseScene>());
        Input::get()->isKeyAccepted = true;
    }

#ifdef DEVELOP_MODE
    if (event.keysym.sym == SDLK_KP_0) {
        viewport.switchCamera();
    }
#endif
}

void WorldScene::buildCommandBuffers() {
    VkClearValue clearColor = { 0.77, 0.83, 0.83, 1.0 };

    VkRenderPassBeginInfo renderPassInfo = {};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.renderPass = Vulkan::Manager::get()->getRenderPass()->getHandle();
    renderPassInfo.renderArea.offset = { 0, 0 };
    renderPassInfo.renderArea.extent = Vulkan::Manager::get()->getSwapchain()->getExtent();
    renderPassInfo.clearValueCount = 1;
    renderPassInfo.pClearValues = &clearColor;

    for (size_t i = 0; i < commandBuffers->getCount(); i++) {
        renderPassInfo.framebuffer = Vulkan::Manager::get()->getFramebuffer(i)->getHandle();

        Vulkan::CommandBuffer commandBuffer(commandBuffers->at(i));
        commandBuffer.begin();

        vkCmdBeginRenderPass(commandBuffer.getHandle(), &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

        vkCmdBindPipeline(commandBuffer.getHandle(), VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline->getHandle());

        VkBuffer vertexBuffers[] = { vertexBuffer->getHandle() };
        VkDeviceSize offsets[] = { 0 };
        vkCmdBindVertexBuffers(commandBuffer.getHandle(), 0, 1, vertexBuffers, offsets);
        vkCmdBindIndexBuffer(commandBuffer.getHandle(), indexBuffer->getHandle(), 0, VK_INDEX_TYPE_UINT16);

        VkViewport viewport = {};
        viewport.width = Vulkan::Manager::get()->getSwapchain()->getExtent().width;
        viewport.height = Vulkan::Manager::get()->getSwapchain()->getExtent().height;
        commandBuffer.addViewport(viewport);
        commandBuffer.setViewports(0);

        VkRect2D scissor = {};
        scissor.extent = Vulkan::Manager::get()->getSwapchain()->getExtent();
        vkCmdSetScissor(commandBuffer.getHandle(), 0, 1, &scissor);

        vkCmdBindDescriptorSets(commandBuffer.getHandle(), VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout->getHandle(), 0, descriptorSets->getCount(), descriptorSets->getData(), 0, nullptr);
        vkCmdDrawIndexed(commandBuffer.getHandle(), plane.getIndices().size(), 1, 0, 0, 0);
        vkCmdEndRenderPass(commandBuffer.getHandle());

        commandBuffer.end();
    }
}

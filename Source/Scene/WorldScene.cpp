#include "WorldScene.h"
#include "../ECS/Engine.h"
#include "../ECS/System.h"
#include "../ECS/EntityBuilder.h"
#include "../ECS/Components/Components.h"
#include "../ECS/Systems/Systems.h"
#include "../Resource/ResourceManager.h"
#include "../GameState/GameStateManager.h"
#include "../Event/Input.h"
#include "../Graphics/Vulkan/Manager.h"
#include "../Resource/ShaderResource.h"
#include "../Resource/ResourceManager.h"
#include "../Graphics/Vulkan/Command/CommandBuffer.h"

WorldScene::WorldScene() {

}

WorldScene::~WorldScene() {
    delete commandBufferCollection;
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
    delete indexMemoryBuffer;
    delete vertexMemoryBuffer;
}

void WorldScene::init() {
    const std::vector<glm::vec2> vertices = {
        { -1.0f, -1.0f },
        {  1.0f, -1.0f },
        {  1.0f,  1.0f },
        { -1.0f,  1.0f },
    };

    const std::vector<uint16_t> indices = {
        0, 1, 2, 2, 3, 0
    };

    vertexMemoryBuffer = new Vulkan::MemoryBuffer(device, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, sizeof(vertices[0]) * vertices.size(), vertices.data());
    vertexMemoryBuffer->update();

    indexMemoryBuffer = new Vulkan::MemoryBuffer(device, VK_BUFFER_USAGE_INDEX_BUFFER_BIT, sizeof(indices[0]) * indices.size(), indices.data());
    indexMemoryBuffer->update();

    uniformFrag = new Vulkan::Descriptor(device, VK_SHADER_STAGE_FRAGMENT_BIT, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
                                      VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 0, sizeof(ubo), &ubo);

    octreeBuffer = new Vulkan::Descriptor(device, VK_SHADER_STAGE_FRAGMENT_BIT, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT,
                                      VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 1, MEMORY_SIZE, &octreeFrag);

    renderListBuffer = new Vulkan::Descriptor(device, VK_SHADER_STAGE_FRAGMENT_BIT, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT,
                                      VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 2, MAX_OCTREE_COUNT, &renderList);

    pickResultBuffer = new Vulkan::Descriptor(device, VK_SHADER_STAGE_FRAGMENT_BIT, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT,
                                      VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 3, sizeof(pickResult), &pickResult);

    debugOutBuffer = new Vulkan::Descriptor(device, VK_SHADER_STAGE_FRAGMENT_BIT, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT,
                                      VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 4, sizeof(debugOut), &debugOut);

    descriptorPool = new Vulkan::DescriptorPool(device);
    descriptorPool->addPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER);
    descriptorPool->addPoolSize(VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 4);
    descriptorPool->create();

    descriptorSetLayout = new Vulkan::DescriptorSetLayout(device);

    descriptorSetLayout->addLayoutBinding(*uniformFrag->getLayoutBinding());
    descriptorSetLayout->addLayoutBinding(*octreeBuffer->getLayoutBinding());
    descriptorSetLayout->addLayoutBinding(*renderListBuffer->getLayoutBinding());
    descriptorSetLayout->addLayoutBinding(*pickResultBuffer->getLayoutBinding());
    descriptorSetLayout->addLayoutBinding(*debugOutBuffer->getLayoutBinding());
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

    ShaderResource* shaderResource = ResourceManager::get()->getResource<ShaderResource>("VoxelVertShader");
    graphicsPipeline->addShaderCode(VK_SHADER_STAGE_VERTEX_BIT, "main", (size_t)shaderResource->getSize(), (uint32_t*)shaderResource->getData());

    shaderResource = ResourceManager::get()->getResource<ShaderResource>("VoxelFragShader");
    graphicsPipeline->addShaderCode(VK_SHADER_STAGE_FRAGMENT_BIT, "main", (size_t)shaderResource->getSize(), (uint32_t*)shaderResource->getData());

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
    graphicsPipeline->setPipelineLayout(pipelineLayout);
    graphicsPipeline->setRenderPass(Vulkan::Manager::get()->getRenderPass());
    graphicsPipeline->create();

    commandBufferCollection = new Vulkan::CommandBufferCollection(device, Vulkan::Manager::get()->getCommandPool());
    commandBufferCollection->allocate(Vulkan::Manager::get()->getSwapchain()->getImageCount());

    for (size_t i = 0; i < commandBufferCollection->getCount(); i++) {
        Vulkan::CommandBuffer commandBuffer(commandBufferCollection->at(i));
        commandBuffer.begin();

        VkClearValue clearColor = { 0.77, 0.83, 0.83, 1.0 };

        VkRenderPassBeginInfo renderPassInfo = {};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.renderPass = Vulkan::Manager::get()->getRenderPass()->getHandle();
        renderPassInfo.framebuffer = Vulkan::Manager::get()->getFramebuffer(i)->getHandle();
        renderPassInfo.renderArea.offset = { 0, 0 };
        renderPassInfo.renderArea.extent = Vulkan::Manager::get()->getSwapchain()->getExtent();
        renderPassInfo.clearValueCount = 1;
        renderPassInfo.pClearValues = &clearColor;

        vkCmdBeginRenderPass(commandBuffer.getHandle(), &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

        vkCmdBindPipeline(commandBuffer.getHandle(), VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline->getHandle());

        VkBuffer vertexBuffers[] = { vertexMemoryBuffer->getBuffer()->getHandle() };
        VkDeviceSize offsets[] = { 0 };
        vkCmdBindVertexBuffers(commandBuffer.getHandle(), 0, 1, vertexBuffers, offsets);
        vkCmdBindIndexBuffer(commandBuffer.getHandle(), indexMemoryBuffer->getBuffer()->getHandle(), 0, VK_INDEX_TYPE_UINT16);

        VkViewport viewport = {};
        viewport.width = Vulkan::Manager::get()->getSwapchain()->getExtent().width;
        viewport.height = Vulkan::Manager::get()->getSwapchain()->getExtent().height;
        vkCmdSetViewport(commandBuffer.getHandle(), 0, 1, &viewport);

        VkRect2D scissor = {};
        scissor.extent = Vulkan::Manager::get()->getSwapchain()->getExtent();
        vkCmdSetScissor(commandBuffer.getHandle(), 0, 1, &scissor);

        vkCmdBindDescriptorSets(commandBuffer.getHandle(), VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout->getHandle(), 0, descriptorSets->getCount(), descriptorSets->getData(), 0, nullptr);
        vkCmdDrawIndexed(commandBuffer.getHandle(), indices.size(), 1, 0, 0, 0);
        vkCmdEndRenderPass(commandBuffer.getHandle());

        commandBuffer.end();
    }

    Vulkan::Manager::get()->setCommandBuffers(commandBufferCollection);
}

void WorldScene::draw(float dt) {

}

void WorldScene::update(float dt) {
    uniformFrag->update();
//    octreeBuffer->update();
//    renderListBuffer->update();
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

    // Ground
    std::shared_ptr<Entity> ground = EntityBuilder::geometry();
    transformSystem->setScale(ground.get(), 5);
    transformSystem->setPosition(ground.get(), glm::vec3(0.0, 1.0, 0.0));
    OctreeComponent* groundOctree = static_cast<OctreeComponent*>(ground->components[ComponentType::Octree].get());
    groundOctree->data = ResourceManager::get()->getResource<Octree>("GroundOctree")->data();
    Engine::get()->addEntity(ground);
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
    tree1Octree->data = ResourceManager::get()->getResource<Octree>("TreeOctree")->data();
    Engine::get()->addEntity(tree1);
    octreeSystem->getGpuMemoryManager()->addEntity(tree1.get(), octreeBuffer);

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
    octreeSystem->getGpuMemoryManager()->addEntity(tree2.get(), octreeBuffer);

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
    octreeSystem->getGpuMemoryManager()->addEntity(tree3.get(), octreeBuffer);

    // Chamomiles
    std::shared_ptr<Entity> chamomile1 = EntityBuilder::geometry();
    transformSystem->setScale(chamomile1.get(), 0.04);
    transformSystem->setPosition(chamomile1.get(), glm::vec3(0.2, -0.22, 0.2));
    OctreeComponent* chamomile1Octree = static_cast<OctreeComponent*>(chamomile1->components[ComponentType::Octree].get());
    chamomile1Octree->data = ResourceManager::get()->getResource<Octree>("ChamomileOctree")->data();
    Engine::get()->addEntity(chamomile1);
    octreeSystem->getGpuMemoryManager()->addEntity(chamomile1.get(), octreeBuffer);

    std::shared_ptr<Entity> chamomile2 = EntityBuilder::geometry();
    transformSystem->setScale(chamomile2.get(), 0.04);
    transformSystem->setPosition(chamomile2.get(), glm::vec3(-0.3, -0.22, 1.3));
    OctreeComponent* chamomile2Octree = static_cast<OctreeComponent*>(chamomile2->components[ComponentType::Octree].get());
    chamomile2Octree->data = ResourceManager::get()->getResource<Octree>("ChamomileOctree")->data();
    Engine::get()->addEntity(chamomile2);
    octreeSystem->getGpuMemoryManager()->addEntity(chamomile2.get(), octreeBuffer);

    std::shared_ptr<Entity> chamomile3 = EntityBuilder::geometry();
    transformSystem->setScale(chamomile3.get(), 0.04);
    transformSystem->setPosition(chamomile3.get(), glm::vec3(0.4, -0.22, 1.0));
    OctreeComponent* chamomile3Octree = static_cast<OctreeComponent*>(chamomile3->components[ComponentType::Octree].get());
    chamomile3Octree->data = ResourceManager::get()->getResource<Octree>("ChamomileOctree")->data();
    Engine::get()->addEntity(chamomile3);
    octreeSystem->getGpuMemoryManager()->addEntity(chamomile3.get(), octreeBuffer);

    octreeSystem->getGpuMemoryManager()->updateRenderList();

    // Light
    std::shared_ptr<Entity> light = EntityBuilder::light();
    transformSystem->translate(light.get(), glm::vec3(1.5, 2.5, 1.0));
    Engine::get()->addEntity(light);
}

void WorldScene::onKeyPressed(const SDL_KeyboardEvent& event) {
    if (event.keysym.sym == SDLK_ESCAPE) {
        GameStateManager::get()->pushState(GameState::PAUSE);
        Input::get()->isKeyAccepted = true;
    }
}

#include "MenuScene.h"
#include "../Core/App.h"
#include "../GameState/GameStateManager.h"
#include "../Event/Input.h"
#include "../Graphics/Vulkan/Manager.h"
#include "../Resource/ShaderResource.h"
#include "../Resource/ResourceManager.h"
#include "../Graphics/Vulkan/CommandBuffer.h"

MenuScene::MenuScene(int width, int height) :
    Scene2D(width, height) {
}

MenuScene::~MenuScene() {
    delete commandBufferCollection;
    delete graphicsPipeline;
    delete pipelineLayout;
    delete descriptorSetCollection;
    delete descriptorSetLayout;
    delete vertexMemory;
    delete vertexBuffer;
    delete uniformVert;
    delete uniformFrag;
}

void MenuScene::draw(float dt) {

}

void MenuScene::update(float dt) {

}

void MenuScene::create() {
    vertexBuffer = new Vulkan::Buffer(device, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT);

    const std::vector<glm::vec2> vertices = {
        { -1.0f,  1.0f },
        { -1.0f, -1.0f },
        {  1.0f,  1.0f },
        {  1.0f, -1.0f },
    };
    int verticesSize = sizeof(vertices[0]) * vertices.size();
    vertexBuffer->setSize(verticesSize);
    vertexBuffer->create();

    vertexMemory = new Vulkan::DeviceMemory(device);
    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(device->getHandle(), vertexBuffer->getHandle(), &memRequirements);
    vertexMemory->setAllocationSize(memRequirements.size);
    vertexMemory->setMemoryTypeIndex(Vulkan::Manager::get()->getPhysicalDevices()->findMemoryType(device->getPhysicalDevice(), memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT));
    vertexMemory->allocate();

    vkBindBufferMemory(device->getHandle(), vertexBuffer->getHandle(), vertexMemory->getHandle(), 0);

    void* data;
    vkMapMemory(device->getHandle(), vertexMemory->getHandle(), 0, verticesSize, 0, &data);
    memcpy(data, vertices.data(), (size_t) verticesSize);
    vkUnmapMemory(device->getHandle(), vertexMemory->getHandle());

    uniformVert = new Vulkan::Uniform(device);
    uniformFrag = new Vulkan::Uniform(device);

    descriptorSetLayout = new Vulkan::DescriptorSetLayout(device);
    descriptorSetLayout->create();

    descriptorSetCollection = new Vulkan::DescriptorSetCollection(device, Vulkan::Manager::get()->getDescriptorPool());
    descriptorSetCollection->setDescriptorSetLayouts({ descriptorSetLayout->getHandle() });
    descriptorSetCollection->allocate();

    pipelineLayout = new Vulkan::PipelineLayout(device);
    pipelineLayout->setDescriptorSetLayouts({ descriptorSetLayout->getHandle() });
    pipelineLayout->create();

    graphicsPipeline = new Vulkan::Pipeline(Vulkan::PipelineType::Graphics, device);

    ShaderResource* shaderResource = ResourceManager::get()->getResource<ShaderResource>("BaseVertShader");
    graphicsPipeline->addShaderCode(VK_SHADER_STAGE_VERTEX_BIT, "main", (size_t)shaderResource->getSize(), (uint32_t*)shaderResource->getData());

    shaderResource = ResourceManager::get()->getResource<ShaderResource>("BaseFragShader");
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

        VkBuffer vertexBuffers[] = { vertexBuffer->getHandle() };
        VkDeviceSize offsets[] = { 0 };
        vkCmdBindVertexBuffers(commandBuffer.getHandle(), 0, 1, vertexBuffers, offsets);
        vkCmdBindDescriptorSets(commandBuffer.getHandle(), VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout->getHandle(), 0, descriptorSetCollection->getCount(), descriptorSetCollection->getData(), 0, nullptr);
        vkCmdDraw(commandBuffer.getHandle(), vertices.size(), 1, 0, 0);
        vkCmdEndRenderPass(commandBuffer.getHandle());

        commandBuffer.end();
    }

    Vulkan::Manager::get()->setCommandBuffers(commandBufferCollection->getCount(), commandBufferCollection->getData());
}

void MenuScene::onKeyPressed(const SDL_KeyboardEvent& event) {
    if (event.keysym.sym == SDLK_ESCAPE) {
        GameStateManager::get()->popState();
        Input::get()->isKeyAccepted = true;
    }
}

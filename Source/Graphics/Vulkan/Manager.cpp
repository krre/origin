#include "Manager.h"
#include "../../Resource/ShaderResource.h"
#include "../../Resource/ResourceManager.h"
#include <glm/glm.hpp>

using namespace Vulkan;

Manager::Manager() {

}

Manager::~Manager() {
    delete presentQueue;
    delete graphicsQueue;
    delete renderFinishedSemaphore;
    delete imageAvailableSemaphore;
    delete fence;
    delete commandBufferCollection;
    delete descriptorSetCollection;
    delete descriptorPool;
    delete vertexMemory;
    delete vertexBuffer;
    delete commandPool;
    framebuffers.clear();
    delete graphicsPipeline;
    delete pipelineLayout;
    delete descriptorSetLayout;
    delete renderPass;
    imageViews.clear();
    delete swapchain;
    delete surface;
    delete device;
    delete physicalDeviceCollection;
    delete debugCallback;
    delete instance;
}

VkResult Manager::createInstance() {
    instance = new Instance();
    instance->setEnabledLayers({
//        "VK_LAYER_LUNARG_api_dump",
        "VK_LAYER_LUNARG_image",
        "VK_LAYER_LUNARG_parameter_validation",
//        "VK_LAYER_LUNARG_vktrace",
        "VK_LAYER_LUNARG_core_validation",
        "VK_LAYER_LUNARG_screenshot",
        "VK_LAYER_LUNARG_swapchain",
        "VK_LAYER_LUNARG_object_tracker",
        "VK_LAYER_GOOGLE_unique_objects",
        "VK_LAYER_GOOGLE_threading",
        "VK_LAYER_LUNARG_standard_validation"
    });
    return instance->create();
}

bool Manager::init() {
    if (enableValidationLayers) {
        debugCallback = new DebugReportCallback(instance);
        if (debugCallback->create() != VK_SUCCESS) {
            return false;
        }
    }

    physicalDeviceCollection = new PhysicalDeviceCollection(instance);
    mainPhysicalDevice = physicalDeviceCollection->findDevice(VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU);
    if (mainPhysicalDevice == VK_NULL_HANDLE) {
        mainPhysicalDevice = physicalDeviceCollection->findDevice(VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU);
    }

    graphicsFamily = physicalDeviceCollection->findQueue(mainPhysicalDevice, VK_QUEUE_GRAPHICS_BIT);

    device = new Device(mainPhysicalDevice, graphicsFamily);
    if (device->create() != VK_SUCCESS) {
        return false;
    }

    graphicsQueue = new SubmitQueue(device, graphicsFamily, 0);
    presentQueue = new PresentQueue(device, 0, 0); // TODO: Set family index and queue index

    surface = new Surface(instance, mainPhysicalDevice);
    if (surface->create() != VK_SUCCESS) {
        return false;
    }

    swapchain = new Swapchain(device, surface);
    if (swapchain->create() != VK_SUCCESS) {
        return false;
    }

    for (uint32_t i = 0; i < swapchain->getImageCount(); i++) {
        std::shared_ptr<ImageView> imageView(new ImageView(device, surface, swapchain->getImage(i)));
        if (imageView->create() != VK_SUCCESS) {
            return false;
        }
        imageViews.push_back(imageView);
    }

    renderPass = new RenderPass(device, surface);
    if (renderPass->create() != VK_SUCCESS) {
        return false;
    }

    descriptorSetLayout = new DescriptorSetLayout(device);

    if (descriptorSetLayout->create() != VK_SUCCESS) {
        return false;
    }

    pipelineLayout = new PipelineLayout(device);
    pipelineLayout->setDescriptorSetLayouts({ descriptorSetLayout->getHandle() });
    if (pipelineLayout->create() != VK_SUCCESS) {
        return false;
    }

    graphicsPipeline = new Pipeline(PipelineType::Graphics, device);
    ShaderResource* shaderResource;

    shaderResource = ResourceManager::get()->getResource<ShaderResource>("VoxelVertShader");
    graphicsPipeline->addShaderCode(ShaderType::Vertex, (size_t)shaderResource->getSize(), (uint32_t*)shaderResource->getData());

    shaderResource = ResourceManager::get()->getResource<ShaderResource>("VoxelFragShader");
    graphicsPipeline->addShaderCode(ShaderType::Fragment, (size_t)shaderResource->getSize(), (uint32_t*)shaderResource->getData());

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

    graphicsPipeline->setExtent(swapchain->getExtent());
    graphicsPipeline->setPipelineLayout(pipelineLayout);
    graphicsPipeline->setRenderPass(renderPass);

    if (graphicsPipeline->create() != VK_SUCCESS) {
        return false;
    }

    for (uint32_t i = 0; i < swapchain->getImageCount(); i++) {
        std::shared_ptr<Framebuffer> framebuffer(new Framebuffer(device, renderPass, imageViews[i].get(), swapchain->getExtent()));
        if (framebuffer->create() != VK_SUCCESS) {
            return false;
        }
        framebuffers.push_back(framebuffer);
    }

    commandPool = new CommandPool(device, graphicsFamily);
    if (commandPool->create() != VK_SUCCESS) {
        return false;
    }
    commandPool->reset();

    vertexBuffer = new Buffer(device, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT);

    const std::vector<glm::vec2> vertices = {
        { -1.0f,  1.0f },
        { -1.0f, -1.0f },
        {  1.0f,  1.0f },
        {  1.0f, -1.0f },
    };
    int verticesSize = sizeof(vertices[0]) * vertices.size();
    vertexBuffer->setSize(verticesSize);
    vertexBuffer->create();

    vertexMemory = new DeviceMemory(device);
    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(device->getHandle(), vertexBuffer->getHandle(), &memRequirements);
    vertexMemory->setAllocationSize(memRequirements.size);
    vertexMemory->setMemoryTypeIndex(physicalDeviceCollection->findMemoryType(mainPhysicalDevice, memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT));
    vertexMemory->allocate();

    vkBindBufferMemory(device->getHandle(), vertexBuffer->getHandle(), vertexMemory->getHandle(), 0);

    void* data;
    vkMapMemory(device->getHandle(), vertexMemory->getHandle(), 0, verticesSize, 0, &data);
    memcpy(data, vertices.data(), (size_t) verticesSize);
    vkUnmapMemory(device->getHandle(), vertexMemory->getHandle());

    descriptorPool = new DescriptorPool(device);
    if (descriptorPool->create() != VK_SUCCESS) {
        return false;
    }

    descriptorSetCollection = new DescriptorSetCollection(device, descriptorPool);
    descriptorSetCollection->setDescriptorSetLayouts({ descriptorSetLayout->getHandle() });
    if (descriptorSetCollection->allocate() != VK_SUCCESS) {
        return false;
    }

    commandBufferCollection = new CommandBufferCollection(device, commandPool);
    if (commandBufferCollection->allocate(swapchain->getImageCount()) != VK_SUCCESS) {
        return false;
    }

    for (size_t i = 0; i < commandBufferCollection->getCount(); i++) {
        CommandBuffer commandBuffer(commandBufferCollection->at(i));
        commandBuffer.begin();

        VkClearValue clearColor = { 0.77, 0.83, 0.83, 1.0 };

        VkRenderPassBeginInfo renderPassInfo = {};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.renderPass = renderPass->getHandle();
        renderPassInfo.framebuffer = framebuffers[i]->getHandle();
        renderPassInfo.renderArea.offset = { 0, 0 };
        renderPassInfo.renderArea.extent = swapchain->getExtent();
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

    fence = new Fence(device);
    if (fence->create() != VK_SUCCESS) {
        return false;
    }

    imageAvailableSemaphore = new Semaphore(device);
    if (imageAvailableSemaphore->create() != VK_SUCCESS) {
        return false;
    }

    renderFinishedSemaphore = new Semaphore(device);
    if (renderFinishedSemaphore->create() != VK_SUCCESS) {
        return false;
    }

    graphicsQueue->setSignalSemaphores({ renderFinishedSemaphore->getHandle() });
    graphicsQueue->setWaitSemaphores({ imageAvailableSemaphore->getHandle() });
    graphicsQueue->setWaitDstStageMask({ VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT });
    graphicsQueue->setCommandBuffersCount(commandBufferCollection->getCount());
    graphicsQueue->setCommandBuffersData(commandBufferCollection->getData());

    presentQueue->setWaitSemaphores({ renderFinishedSemaphore->getHandle() });
    presentQueue->setSwapchains({ swapchain->getHandle() });
    presentQueue->setImageIndices(&swapchainImageIndex);

    return true;
}

void Manager::drawFrame() {
    vkAcquireNextImageKHR(device->getHandle(), swapchain->getHandle(), std::numeric_limits<uint64_t>::max(), imageAvailableSemaphore->getHandle(), VK_NULL_HANDLE, &swapchainImageIndex);
    graphicsQueue->submit();
    presentQueue->present();
}

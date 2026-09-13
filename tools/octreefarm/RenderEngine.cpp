#include "RenderEngine.h"
#include "Viewport.h"
#include "octree/Octree.h"
#include <QApplication>
#include <QFile>
#include <QVulkanWindow>
#include <algorithm>
#include <cstddef>
#include <cstring>
#include <stdexcept>

void check(VkResult result, const char* operation) {
    if (result != VK_SUCCESS) {
        throw std::runtime_error(std::string(operation) + " failed: " + std::to_string(result));
    }
}

RenderEngine::RenderEngine(QVulkanWindow* window) : m_window(window) {
}

RenderEngine::~RenderEngine() {
    releaseSwapChainResources();
    releaseResources();
}

void RenderEngine::setVoxelVertices(const void* vertices, uint32_t count, uint32_t byteSize) {
    m_voxelRenderPass.vertexCount = count;
    m_voxelVertexData.resize(byteSize);

    if (byteSize) {
        std::memcpy(m_voxelVertexData.data(), vertices, byteSize);
    }

    if (isReady() && byteSize) {
        ensureBufferCapacity(m_voxelVertices, byteSize, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT);
        writeBuffer(m_voxelVertices, m_voxelVertexData.data(), byteSize);
    }
}

void RenderEngine::setLineVertices(const void* vertices, uint32_t count, uint32_t byteSize) {
    m_lineRenderPass.vertexCount = count;
    m_lineVertexData.resize(byteSize);

    if (byteSize) {
        std::memcpy(m_lineVertexData.data(), vertices, byteSize);
    }

    if (isReady() && byteSize) {
        ensureBufferCapacity(m_lineVertices, byteSize, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT);
        writeBuffer(m_lineVertices, m_lineVertexData.data(), byteSize);
    }
}

void RenderEngine::updateMvp(const glm::mat4& mvp) {
    m_voxelUbo.mvp = mvp;
    m_lineUbo.mvp = mvp;
}

void RenderEngine::updateShadeless(bool shadeless) {
    m_voxelUbo.shadeless = shadeless;
}

void RenderEngine::initResources() {
    m_device = m_window->device();
    m_physicalDevice = m_window->physicalDevice();
    m_deviceFunctions = m_window->vulkanInstance()->deviceFunctions(m_device);
    m_instanceFunctions = m_window->vulkanInstance()->functions();
    m_frameCount = m_window->concurrentFrameCount();

    createBuffer(m_voxelVertices, InitialBufferSize, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT);
    createBuffer(m_lineVertices, InitialBufferSize, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT);
    m_voxelUniforms.resize(m_frameCount);
    m_lineUniforms.resize(m_frameCount);

    for (uint32_t i = 0; i < m_frameCount; ++i) {
        createBuffer(m_voxelUniforms[i], sizeof(VoxelUBO), VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT);
        createBuffer(m_lineUniforms[i], sizeof(LineUBO), VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT);
    }

    createDescriptors();

    m_voxelVertexShader = createShaderModule("OctreeFarm/FrontLightOctree.vert.spv");
    m_voxelFragmentShader = createShaderModule("OctreeFarm/FrontLightOctree.frag.spv");
    m_lineVertexShader = createShaderModule("Line.vert.spv");
    m_lineFragmentShader = createShaderModule("Line.frag.spv");

    if (!m_voxelVertexData.empty()) {
        ensureBufferCapacity(m_voxelVertices, m_voxelVertexData.size(), VK_BUFFER_USAGE_VERTEX_BUFFER_BIT);
        writeBuffer(m_voxelVertices, m_voxelVertexData.data(), m_voxelVertexData.size());
    }

    if (!m_lineVertexData.empty()) {
        ensureBufferCapacity(m_lineVertices, m_lineVertexData.size(), VK_BUFFER_USAGE_VERTEX_BUFFER_BIT);
        writeBuffer(m_lineVertices, m_lineVertexData.data(), m_lineVertexData.size());
    }
}

void RenderEngine::initSwapChainResources() {
    createPipelines();
}

void RenderEngine::releaseSwapChainResources() {
    destroyPipelines();
}

void RenderEngine::releaseResources() {
    if (m_device == VK_NULL_HANDLE) {
        return;
    }

    destroyPipelines();

    if (m_voxelVertexShader) m_deviceFunctions->vkDestroyShaderModule(m_device, m_voxelVertexShader, nullptr);
    if (m_voxelFragmentShader) m_deviceFunctions->vkDestroyShaderModule(m_device, m_voxelFragmentShader, nullptr);
    if (m_lineVertexShader) m_deviceFunctions->vkDestroyShaderModule(m_device, m_lineVertexShader, nullptr);
    if (m_lineFragmentShader) m_deviceFunctions->vkDestroyShaderModule(m_device, m_lineFragmentShader, nullptr);

    m_voxelVertexShader = m_voxelFragmentShader = m_lineVertexShader = m_lineFragmentShader = VK_NULL_HANDLE;

    destroyDescriptors();
    destroyBuffer(m_voxelVertices);
    destroyBuffer(m_lineVertices);

    for (Buffer& buffer : m_voxelUniforms) destroyBuffer(buffer);
    for (Buffer& buffer : m_lineUniforms) destroyBuffer(buffer);

    m_voxelUniforms.clear();
    m_lineUniforms.clear();
    m_device = VK_NULL_HANDLE;
    m_physicalDevice = VK_NULL_HANDLE;
    m_deviceFunctions = nullptr;
    m_instanceFunctions = nullptr;
    m_frameCount = 0;
}

void RenderEngine::startNextFrame() {
    updateCurrentUniforms();

    const QSize imageSize = m_window->swapChainImageSize();
    VkClearValue clearValues[2] = {};
    clearValues[0].color = {{ 0.9f, 1.0f, 1.0f, 1.0f }};
    clearValues[1].depthStencil = { 1.0f, 0 };
    VkRenderPassBeginInfo renderPassBegin = { VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO };
    renderPassBegin.renderPass = m_window->defaultRenderPass();
    renderPassBegin.framebuffer = m_window->currentFramebuffer();
    renderPassBegin.renderArea.extent = { uint32_t(imageSize.width()), uint32_t(imageSize.height()) };
    renderPassBegin.clearValueCount = 2;
    renderPassBegin.pClearValues = clearValues;

    VkCommandBuffer commandBuffer = m_window->currentCommandBuffer();
    m_deviceFunctions->vkCmdBeginRenderPass(commandBuffer, &renderPassBegin, VK_SUBPASS_CONTENTS_INLINE);

    const uint32_t frame = m_window->currentFrame();

    if (m_voxelRenderPass.vertexCount) {
        recordDraw(commandBuffer, m_voxelRenderPass.pipeline, m_voxelDescriptorSets[frame],
                   m_voxelVertices.handle, m_voxelRenderPass.vertexCount);
    }

    if (m_lineRenderPass.vertexCount) {
        recordDraw(commandBuffer, m_lineRenderPass.pipeline, m_lineDescriptorSets[frame],
                   m_lineVertices.handle, m_lineRenderPass.vertexCount);
    }

    m_deviceFunctions->vkCmdEndRenderPass(commandBuffer);
    m_window->frameReady();
}

void RenderEngine::createBuffer(Buffer& buffer, VkDeviceSize size, VkBufferUsageFlags usage) {
    VkBufferCreateInfo bufferInfo = { VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO };
    bufferInfo.size = size;
    bufferInfo.usage = usage;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    check(m_deviceFunctions->vkCreateBuffer(m_device, &bufferInfo, nullptr, &buffer.handle), "vkCreateBuffer");

    VkMemoryRequirements requirements;
    m_deviceFunctions->vkGetBufferMemoryRequirements(m_device, buffer.handle, &requirements);
    VkMemoryAllocateInfo allocationInfo = { VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO };
    allocationInfo.allocationSize = requirements.size;
    allocationInfo.memoryTypeIndex = findMemoryType(requirements.memoryTypeBits,
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
    check(m_deviceFunctions->vkAllocateMemory(m_device, &allocationInfo, nullptr, &buffer.memory), "vkAllocateMemory");
    check(m_deviceFunctions->vkBindBufferMemory(m_device, buffer.handle, buffer.memory, 0), "vkBindBufferMemory");
    buffer.size = size;
}

void RenderEngine::destroyBuffer(Buffer& buffer) {
    if (buffer.handle) m_deviceFunctions->vkDestroyBuffer(m_device, buffer.handle, nullptr);
    if (buffer.memory) m_deviceFunctions->vkFreeMemory(m_device, buffer.memory, nullptr);
    buffer = {};
}

void RenderEngine::writeBuffer(const Buffer& buffer, const void* data, VkDeviceSize size) {
    void* mapped = nullptr;
    check(m_deviceFunctions->vkMapMemory(m_device, buffer.memory, 0, size, 0, &mapped), "vkMapMemory");
    std::memcpy(mapped, data, size);
    m_deviceFunctions->vkUnmapMemory(m_device, buffer.memory);
}

void RenderEngine::ensureBufferCapacity(Buffer& buffer, VkDeviceSize required, VkBufferUsageFlags usage) {
    if (required <= buffer.size) return;
    const VkDeviceSize newSize = std::max<VkDeviceSize>(required, std::max<VkDeviceSize>(InitialBufferSize, buffer.size * 2));
    m_deviceFunctions->vkDeviceWaitIdle(m_device);
    destroyBuffer(buffer);
    createBuffer(buffer, newSize, usage);
}

uint32_t RenderEngine::findMemoryType(uint32_t typeBits, VkMemoryPropertyFlags properties) const {
    VkPhysicalDeviceMemoryProperties memoryProperties;
    m_instanceFunctions->vkGetPhysicalDeviceMemoryProperties(m_physicalDevice, &memoryProperties);

    for (uint32_t i = 0; i < memoryProperties.memoryTypeCount; ++i) {
        if ((typeBits & (1u << i)) && (memoryProperties.memoryTypes[i].propertyFlags & properties) == properties) {
            return i;
        }
    }

    throw std::runtime_error("No suitable Vulkan memory type");
}

VkShaderModule RenderEngine::createShaderModule(const QString& relativePath) const {
    QFile shader(QApplication::applicationDirPath() + "/data/shader/" + relativePath);

    if (!shader.open(QIODevice::ReadOnly)) {
        throw std::runtime_error("Cannot open shader: " + shader.fileName().toStdString());
    }

    const QByteArray code = shader.readAll();

    if (code.isEmpty() || code.size() % int(sizeof(uint32_t))) {
        throw std::runtime_error("Invalid SPIR-V shader: " + shader.fileName().toStdString());
    }

    VkShaderModuleCreateInfo createInfo = { VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO };
    createInfo.codeSize = size_t(code.size());
    createInfo.pCode = reinterpret_cast<const uint32_t*>(code.constData());
    VkShaderModule module = VK_NULL_HANDLE;
    check(m_deviceFunctions->vkCreateShaderModule(m_device, &createInfo, nullptr, &module), "vkCreateShaderModule");
    return module;
}

VkPipeline RenderEngine::createPipeline(VkShaderModule vertexShader, VkShaderModule fragmentShader,
                                        VkPrimitiveTopology topology, uint32_t stride,
                                        const std::vector<VkVertexInputAttributeDescription>& attributes,
                                        VkPipelineLayout layout) const {
    VkPipelineShaderStageCreateInfo stages[2] = {};
    stages[0] = { VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO };
    stages[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
    stages[0].module = vertexShader;
    stages[0].pName = "main";
    stages[1] = { VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO };
    stages[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    stages[1].module = fragmentShader;
    stages[1].pName = "main";

    VkVertexInputBindingDescription binding = { 0, stride, VK_VERTEX_INPUT_RATE_VERTEX };
    VkPipelineVertexInputStateCreateInfo vertexInput = { VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO };
    vertexInput.vertexBindingDescriptionCount = 1;
    vertexInput.pVertexBindingDescriptions = &binding;
    vertexInput.vertexAttributeDescriptionCount = uint32_t(attributes.size());
    vertexInput.pVertexAttributeDescriptions = attributes.data();
    VkPipelineInputAssemblyStateCreateInfo inputAssembly = { VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO };
    inputAssembly.topology = topology;
    VkPipelineViewportStateCreateInfo viewport = { VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO };
    viewport.viewportCount = 1;
    viewport.scissorCount = 1;
    VkPipelineRasterizationStateCreateInfo rasterization = { VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO };
    rasterization.polygonMode = VK_POLYGON_MODE_FILL;
    rasterization.cullMode = VK_CULL_MODE_BACK_BIT;
    rasterization.frontFace = VK_FRONT_FACE_CLOCKWISE;
    rasterization.lineWidth = 1.0f;
    VkPipelineMultisampleStateCreateInfo multisample = { VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO };
    multisample.rasterizationSamples = m_window->sampleCountFlagBits();
    VkPipelineDepthStencilStateCreateInfo depthStencil = { VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO };
    depthStencil.depthTestEnable = VK_TRUE;
    depthStencil.depthWriteEnable = VK_TRUE;
    depthStencil.depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL;
    VkPipelineColorBlendAttachmentState colorAttachment = {};
    colorAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
    colorAttachment.blendEnable = VK_TRUE;
    colorAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
    colorAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
    colorAttachment.colorBlendOp = VK_BLEND_OP_ADD;
    colorAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
    colorAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
    colorAttachment.alphaBlendOp = VK_BLEND_OP_ADD;
    VkPipelineColorBlendStateCreateInfo colorBlend = { VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO };
    colorBlend.attachmentCount = 1;
    colorBlend.pAttachments = &colorAttachment;
    const VkDynamicState dynamicStates[] = { VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR };
    VkPipelineDynamicStateCreateInfo dynamic = { VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO };
    dynamic.dynamicStateCount = 2;
    dynamic.pDynamicStates = dynamicStates;
    VkGraphicsPipelineCreateInfo createInfo = { VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO };
    createInfo.stageCount = 2;
    createInfo.pStages = stages;
    createInfo.pVertexInputState = &vertexInput;
    createInfo.pInputAssemblyState = &inputAssembly;
    createInfo.pViewportState = &viewport;
    createInfo.pRasterizationState = &rasterization;
    createInfo.pMultisampleState = &multisample;
    createInfo.pDepthStencilState = &depthStencil;
    createInfo.pColorBlendState = &colorBlend;
    createInfo.pDynamicState = &dynamic;
    createInfo.layout = layout;
    createInfo.renderPass = m_window->defaultRenderPass();
    VkPipeline pipeline = VK_NULL_HANDLE;
    check(m_deviceFunctions->vkCreateGraphicsPipelines(m_device, VK_NULL_HANDLE, 1, &createInfo, nullptr, &pipeline), "vkCreateGraphicsPipelines");
    return pipeline;
}

void RenderEngine::createDescriptors() {
    VkDescriptorSetLayoutBinding binding = {};
    binding.binding = 0;
    binding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    binding.descriptorCount = 1;
    binding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
    VkDescriptorSetLayoutCreateInfo layoutInfo = { VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO };
    layoutInfo.bindingCount = 1;
    layoutInfo.pBindings = &binding;
    check(m_deviceFunctions->vkCreateDescriptorSetLayout(m_device, &layoutInfo, nullptr, &m_voxelDescriptorSetLayout), "vkCreateDescriptorSetLayout");
    check(m_deviceFunctions->vkCreateDescriptorSetLayout(m_device, &layoutInfo, nullptr, &m_lineDescriptorSetLayout), "vkCreateDescriptorSetLayout");

    VkDescriptorPoolSize poolSize = { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, m_frameCount * 2 };
    VkDescriptorPoolCreateInfo poolInfo = { VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO };
    poolInfo.maxSets = m_frameCount * 2;
    poolInfo.poolSizeCount = 1;
    poolInfo.pPoolSizes = &poolSize;
    check(m_deviceFunctions->vkCreateDescriptorPool(m_device, &poolInfo, nullptr, &m_descriptorPool), "vkCreateDescriptorPool");

    auto allocate = [this](VkDescriptorSetLayout layout, std::vector<VkDescriptorSet>& sets) {
        sets.resize(m_frameCount);
        std::vector<VkDescriptorSetLayout> layouts(m_frameCount, layout);
        VkDescriptorSetAllocateInfo allocationInfo = { VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO };
        allocationInfo.descriptorPool = m_descriptorPool;
        allocationInfo.descriptorSetCount = m_frameCount;
        allocationInfo.pSetLayouts = layouts.data();
        check(m_deviceFunctions->vkAllocateDescriptorSets(m_device, &allocationInfo, sets.data()), "vkAllocateDescriptorSets");
    };

    allocate(m_voxelDescriptorSetLayout, m_voxelDescriptorSets);
    allocate(m_lineDescriptorSetLayout, m_lineDescriptorSets);

    for (uint32_t i = 0; i < m_frameCount; ++i) {
        const VkDescriptorBufferInfo voxelInfo = { m_voxelUniforms[i].handle, 0, sizeof(VoxelUBO) };
        const VkWriteDescriptorSet voxelWrite = { VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET, nullptr, m_voxelDescriptorSets[i], 0, 0, 1, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, nullptr, &voxelInfo, nullptr };
        m_deviceFunctions->vkUpdateDescriptorSets(m_device, 1, &voxelWrite, 0, nullptr);
        const VkDescriptorBufferInfo lineInfo = { m_lineUniforms[i].handle, 0, sizeof(LineUBO) };
        const VkWriteDescriptorSet lineWrite = { VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET, nullptr, m_lineDescriptorSets[i], 0, 0, 1, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, nullptr, &lineInfo, nullptr };
        m_deviceFunctions->vkUpdateDescriptorSets(m_device, 1, &lineWrite, 0, nullptr);
    }

    auto createPipelineLayout = [this](VkDescriptorSetLayout descriptorSetLayout, VkPipelineLayout& pipelineLayout) {
        VkPipelineLayoutCreateInfo info = { VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO };
        info.setLayoutCount = 1;
        info.pSetLayouts = &descriptorSetLayout;
        check(m_deviceFunctions->vkCreatePipelineLayout(m_device, &info, nullptr, &pipelineLayout), "vkCreatePipelineLayout");
    };
    createPipelineLayout(m_voxelDescriptorSetLayout, m_voxelPipelineLayout);
    createPipelineLayout(m_lineDescriptorSetLayout, m_linePipelineLayout);
}

void RenderEngine::destroyDescriptors() {
    if (m_voxelPipelineLayout) m_deviceFunctions->vkDestroyPipelineLayout(m_device, m_voxelPipelineLayout, nullptr);
    if (m_linePipelineLayout) m_deviceFunctions->vkDestroyPipelineLayout(m_device, m_linePipelineLayout, nullptr);
    if (m_descriptorPool) m_deviceFunctions->vkDestroyDescriptorPool(m_device, m_descriptorPool, nullptr);
    if (m_voxelDescriptorSetLayout) m_deviceFunctions->vkDestroyDescriptorSetLayout(m_device, m_voxelDescriptorSetLayout, nullptr);
    if (m_lineDescriptorSetLayout) m_deviceFunctions->vkDestroyDescriptorSetLayout(m_device, m_lineDescriptorSetLayout, nullptr);
    m_voxelPipelineLayout = m_linePipelineLayout = VK_NULL_HANDLE;
    m_descriptorPool = VK_NULL_HANDLE;
    m_voxelDescriptorSetLayout = m_lineDescriptorSetLayout = VK_NULL_HANDLE;
    m_voxelDescriptorSets.clear();
    m_lineDescriptorSets.clear();
}

void RenderEngine::createPipelines() {
    destroyPipelines();

    const std::vector<VkVertexInputAttributeDescription> voxelAttributes = {
        { 0, 0, VK_FORMAT_R32G32B32A32_SFLOAT, offsetof(Octree::Octree::Vertex, pos) },
        { 1, 0, VK_FORMAT_R32G32B32A32_SFLOAT, offsetof(Octree::Octree::Vertex, color) },
        { 2, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Octree::Octree::Vertex, normal) },
    };

    const std::vector<VkVertexInputAttributeDescription> lineAttributes = {
        { 0, 0, VK_FORMAT_R32G32B32A32_SFLOAT, offsetof(Viewport::LineVertex, position) },
        { 1, 0, VK_FORMAT_R32G32B32A32_SFLOAT, offsetof(Viewport::LineVertex, color) },
    };

    m_voxelRenderPass.pipeline = createPipeline(m_voxelVertexShader, m_voxelFragmentShader,
        VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST, sizeof(Octree::Octree::Vertex), voxelAttributes, m_voxelPipelineLayout);
    m_lineRenderPass.pipeline = createPipeline(m_lineVertexShader, m_lineFragmentShader,
        VK_PRIMITIVE_TOPOLOGY_LINE_LIST, sizeof(Viewport::LineVertex), lineAttributes, m_linePipelineLayout);
}

void RenderEngine::destroyPipelines() {
    if (m_device == VK_NULL_HANDLE) return;
    if (m_voxelRenderPass.pipeline) m_deviceFunctions->vkDestroyPipeline(m_device, m_voxelRenderPass.pipeline, nullptr);
    if (m_lineRenderPass.pipeline) m_deviceFunctions->vkDestroyPipeline(m_device, m_lineRenderPass.pipeline, nullptr);

    m_voxelRenderPass.pipeline = VK_NULL_HANDLE;
    m_lineRenderPass.pipeline = VK_NULL_HANDLE;
}

void RenderEngine::updateCurrentUniforms() {
    const uint32_t frame = m_window->currentFrame();
    writeBuffer(m_voxelUniforms[frame], &m_voxelUbo, sizeof(m_voxelUbo));
    writeBuffer(m_lineUniforms[frame], &m_lineUbo, sizeof(m_lineUbo));
}

void RenderEngine::recordDraw(VkCommandBuffer commandBuffer, VkPipeline pipeline, VkDescriptorSet descriptorSet,
                              VkBuffer vertexBuffer, uint32_t vertexCount) const {
    VkViewport viewport = {};
    const QSize imageSize = m_window->swapChainImageSize();
    viewport.width = float(imageSize.width());
    viewport.height = float(imageSize.height());
    viewport.maxDepth = 1.0f;
    const VkRect2D scissor = { { 0, 0 }, { uint32_t(imageSize.width()), uint32_t(imageSize.height()) } };
    m_deviceFunctions->vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);
    m_deviceFunctions->vkCmdSetViewport(commandBuffer, 0, 1, &viewport);
    m_deviceFunctions->vkCmdSetScissor(commandBuffer, 0, 1, &scissor);
    const VkDeviceSize offset = 0;
    m_deviceFunctions->vkCmdBindVertexBuffers(commandBuffer, 0, 1, &vertexBuffer, &offset);
    const VkPipelineLayout layout = pipeline == m_voxelRenderPass.pipeline ? m_voxelPipelineLayout : m_linePipelineLayout;
    m_deviceFunctions->vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, layout, 0, 1, &descriptorSet, 0, nullptr);
    m_deviceFunctions->vkCmdDraw(commandBuffer, vertexCount, 1, 0, 0);
}

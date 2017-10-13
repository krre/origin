#include "ShaderProgram.h"
#include "Graphics/Vulkan/VulkanCore.h"
#include "Graphics/Vulkan/Wrapper/Pipeline/PipelineLayout.h"
#include "Graphics/Vulkan/Wrapper/Pipeline/GraphicsPipeline.h"
#include "Graphics/Vulkan/Wrapper/Descriptor/DescriptorPool.h"
#include "Graphics/Vulkan/Wrapper/Descriptor/DescriptorSetLayout.h"
#include "Graphics/Vulkan/Wrapper/Descriptor/DescriptorSets.h"
#include "Graphics/Vulkan/Wrapper/RenderPass.h"
#include "Resource/ResourceManager.h"
#include "Resource/ShaderResource.h"
#include "Core/Utils.h"
#include "Graphics/Vulkan/Wrapper/Instance.h"
#include "Graphics/Vulkan/Wrapper/Surface/Swapchain.h"
#include "Graphics/Vulkan/Wrapper/Buffer/Buffer.h"
#include "Graphics/Vulkan/Wrapper/Surface/Surface.h"

using namespace Vulkan;

ShaderProgram::ShaderProgram() {
    descriptorPool = std::make_unique<DescriptorPool>();
    descriptorSets = std::make_unique<DescriptorSets>(descriptorPool.get());

    graphicsPipeline = std::make_unique<GraphicsPipeline>();
    graphicsPipeline->setExtent(VulkanCore::get()->getSurface()->getCapabilities().currentExtent);
    graphicsPipeline->setRenderPass(VulkanCore::get()->getSwapchain()->getRenderPass()->getHandle());

    pipelineLayout = std::make_unique<PipelineLayout>();
    descriptorSetLayout = std::make_unique<DescriptorSetLayout>();
}

ShaderProgram::~ShaderProgram() {
    descriptorSets->destroy();
    descriptorPool->destroy();
}

void ShaderProgram::addShader(const std::string& path) {
    ShaderResource* shaderResource = ResourceManager::get()->load<ShaderResource>(path);
    shaderResources.push_back(shaderResource);
    graphicsPipeline->addShaderCode(shaderResource->getStage(), shaderResource->getCodeSize() * sizeof(uint32_t), shaderResource->getCodeData());
}

void ShaderProgram::createPipeline() {
    assert(graphicsPipeline->getHandle() == VK_NULL_HANDLE);

    for (const auto& shaderResource : shaderResources) {
//        shaderResource->dumpBindings();
//        shaderResource->dumpLocations();

        for (auto& bindingIt : shaderResource->bindings) {
            VkDescriptorSetLayoutBinding* layoutBinding = &bindingIt.second;
            if (descriptorsTypes.find(layoutBinding->descriptorType) == descriptorsTypes.end()) {
                descriptorsTypes[layoutBinding->descriptorType] = 1;
            } else {
                descriptorsTypes[layoutBinding->descriptorType]++;
            }

            descriptorSetLayout->addLayoutBinding(*layoutBinding);

            VkWriteDescriptorSet writeDescriptorSet = {};
            writeDescriptorSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
            writeDescriptorSet.dstBinding = layoutBinding->binding;
            writeDescriptorSet.dstArrayElement = 0;
            writeDescriptorSet.descriptorType = layoutBinding->descriptorType;
            writeDescriptorSet.descriptorCount = layoutBinding->descriptorCount;

            const auto& bufferIt = bufferInfos.find(bindingIt.first);
            if (bufferIt != bufferInfos.end()) {
                VkBufferUsageFlagBits usage;
                if (layoutBinding->descriptorType == VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER) {
                    usage = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
                } else if (layoutBinding->descriptorType == VK_DESCRIPTOR_TYPE_STORAGE_BUFFER) {
                    usage = VK_BUFFER_USAGE_STORAGE_BUFFER_BIT;
                }
                BufferInfo* bufferInfo = &bufferIt->second;
                std::shared_ptr<Buffer> buffer = std::make_shared<Buffer>(usage, bufferInfo->size, false);
                buffer->create();
                bufferInfo->buffer = buffer;
                writeDescriptorSet.pBufferInfo = buffer->getDescriptorInfo();
                descriptorSets->addWriteDescriptorSet(writeDescriptorSet);
            }

            const auto& imageIt = imageInfos.find(bindingIt.first);
            if (imageIt != imageInfos.end()) {
                writeDescriptorSet.pImageInfo = &imageIt->second;
                descriptorSets->addWriteDescriptorSet(writeDescriptorSet);
            }
        }

        for (auto& location : shaderResource->locations) {
            const std::string& name = location.first;
            const auto& inputInfoIt = locationInfos.find(name);
            if (inputInfoIt != locationInfos.end()) {
                ShaderResource::Location* input = &location.second;
                locationInfos.at(name).location = input->location;
                locationInfos.at(name).format = input->format;
                graphicsPipeline->addVertexAttributeDescription(locationInfos.at(name));
            }
        }
    }

    descriptorSetLayout->create();
    descriptorSets->addDescriptorSetLayout(descriptorSetLayout->getHandle());
    pipelineLayout->addDescriptorSetLayout(descriptorSetLayout->getHandle());
    pipelineLayout->create();
    graphicsPipeline->setPipelineLayout(pipelineLayout->getHandle());

    // Descriptor pool
    for (const auto& it : descriptorsTypes) {
        descriptorPool->addPoolSize(it.first, it.second);
    }

    descriptorPool->create();
    descriptorSets->allocate();
    descriptorSets->updateDescriptorSets();

    graphicsPipeline->create();
}

int ShaderProgram::createVertexInputBindingDescription(uint32_t stride, VkVertexInputRate inputRate) {
    VkVertexInputBindingDescription bindingDescription = {};
    bindingDescription.binding = vertexBindingCount++;
    bindingDescription.inputRate = inputRate;
    bindingDescription.stride = stride;
    graphicsPipeline->addVertexBindingDescription(bindingDescription);
    return bindingDescription.binding;
}

void ShaderProgram::bindUniform(const std::string& name, uint32_t size, void* uniform) {
    BufferInfo linkInfo = {};
    linkInfo.size = size;
    linkInfo.uniform = uniform;
    bufferInfos[name] = linkInfo;
}

void ShaderProgram::bindImage(const std::string& name, VkDescriptorImageInfo descriptorImageInfo) {
    imageInfos[name] = descriptorImageInfo;
}

void ShaderProgram::bindInput(const std::string& name, uint32_t binding, uint32_t offset) {
    locationInfos[name].binding = binding;
    locationInfos[name].offset = offset;
}

void ShaderProgram::writeUniform(const std::string& name, VkDeviceSize offset, VkDeviceSize size, void* data) {
    bufferInfos.at(name).buffer->write(data != nullptr ? data : bufferInfos.at(name).uniform, size ? size : bufferInfos.at(name).size, offset);
}

void ShaderProgram::readUniform(const std::string& name, VkDeviceSize offset, VkDeviceSize size, void* data) {
    bufferInfos.at(name).buffer->read(data != nullptr ? data : bufferInfos.at(name).uniform, size ? size : bufferInfos.at(name).size, offset);
}

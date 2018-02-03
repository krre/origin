#include "ShaderProgram.h"
#include "Renderer.h"
#include "API/Buffer/Buffer.h"
#include "API/Descriptor/DescriptorPool.h"
#include "API/Descriptor/DescriptorSetLayout.h"
#include "API/Descriptor/DescriptorSets.h"
#include "API/Instance.h"
#include "API/Pipeline/PipelineLayout.h"
#include "API/RenderPass.h"
#include "API/Surface/Surface.h"
#include "API/Surface/Swapchain.h"
#include <fstream>
#include <iostream>
#include <assert.h>
#include <algorithm>
#include <spirv_cross/spirv_cross.hpp>

namespace Vulkan {

ShaderProgram::ShaderProgram() {
    device = Renderer::get()->getGraphicsDevice();

    descriptorPool = std::make_unique<DescriptorPool>(device);
    descriptorSets = std::make_unique<DescriptorSets>(device, descriptorPool.get());

    pipelineLayout = std::make_unique<PipelineLayout>(device);
}

ShaderProgram::~ShaderProgram() {
    descriptorSets->destroy();
    descriptorPool->destroy();
}

void ShaderProgram::loadShader(const std::string& filePath) {
    std::unique_ptr<Shader> shader = std::make_unique<Shader>();
    shader->load(filePath);
    shaders.push_back(std::move(shader));
}

void ShaderProgram::create() {
    std::map<VkDescriptorType, uint32_t> descriptorTypes;

    // Collect descriptor set layouts and descriptor types
    for (const auto& shader : shaders) {
        for (const auto& binding : shader->getBindings()) {
            if (descriptorSetLayouts.find(binding.set) == descriptorSetLayouts.end()) {
                descriptorSetLayouts[binding.set] = std::make_unique<DescriptorSetLayout>(device);
            }

            descriptorSetLayouts.at(binding.set)->addLayoutBinding(binding.layoutBinding);

            if (descriptorTypes.find(binding.layoutBinding.descriptorType) == descriptorTypes.end()) {
                descriptorTypes[binding.layoutBinding.descriptorType] = 0;
            }

            descriptorTypes.at(binding.layoutBinding.descriptorType) += binding.layoutBinding.descriptorCount;
        }
    }

    // Create descriptor pool
    for (const auto& it : descriptorTypes) {
        descriptorPool->addPoolSize(it.first, it.second);
    }

    descriptorPool->setMaxSets(descriptorSetLayouts.size());
    descriptorPool->create();

    // Create descriptor set layouts
    for (const auto& it : descriptorSetLayouts) {
        it.second->create();
        descriptorSets->addDescriptorSetLayout(it.second->getHandle());
        pipelineLayout->addDescriptorSetLayout(it.second->getHandle());
    }

    descriptorSets->allocate();
    pipelineLayout->create();

//    descriptorSets->updateDescriptorSets();
}

void ShaderProgram::createPipeline() {
/*
    for (const auto& shader : shaders) {
//        shader->dumpBindings();
//        shader->dumpLocations();

        for (auto& bindingIt : shader->bindings) {
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
                std::shared_ptr<Buffer> buffer = std::make_shared<Buffer>(device, usage, bufferInfo->size);
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

        for (auto& location : shader->locations) {
            const std::string& name = location.first;
            const auto& inputInfoIt = locationInfos.find(name);
            if (inputInfoIt != locationInfos.end()) {
                Shader::Location* input = &location.second;
                locationInfos.at(name).location = input->location;
                locationInfos.at(name).format = input->format;
                graphicsPipeline->addVertexAttributeDescription(locationInfos.at(name));
            }
        }

        graphicsPipeline->addShaderCode(shader->getStage(), shader->getCodeSize() * sizeof(uint32_t), shader->getCodeData());
    }
*/
}

int ShaderProgram::createVertexInputBindingDescription(uint32_t stride, VkVertexInputRate inputRate) {
    VkVertexInputBindingDescription bindingDescription = {};
//    bindingDescription.binding = vertexBindingCount++;
    bindingDescription.inputRate = inputRate;
    bindingDescription.stride = stride;
//    graphicsPipeline->addVertexBindingDescription(bindingDescription);
    return bindingDescription.binding;
}

void ShaderProgram::bindUniform(const std::string& name, uint32_t size, void* uniform) {
    BufferInfo linkInfo = {};
    linkInfo.size = size;
    linkInfo.uniform = uniform;
//    bufferInfos[name] = linkInfo;
}

void ShaderProgram::bindImage(const std::string& name, VkDescriptorImageInfo descriptorImageInfo) {
//    imageInfos[name] = descriptorImageInfo;
}

void ShaderProgram::bindInput(const std::string& name, uint32_t binding, uint32_t offset) {
//    locationInfos[name].binding = binding;
//    locationInfos[name].offset = offset;
}

void ShaderProgram::writeUniform(const std::string& name, VkDeviceSize offset, VkDeviceSize size, void* data) {
//    bufferInfos.at(name).buffer->write(data != nullptr ? data : bufferInfos.at(name).uniform, size ? size : bufferInfos.at(name).size, offset);
}

void ShaderProgram::readUniform(const std::string& name, VkDeviceSize offset, VkDeviceSize size, void* data) {
//    bufferInfos.at(name).buffer->read(data != nullptr ? data : bufferInfos.at(name).uniform, size ? size : bufferInfos.at(name).size, offset);
}

} // Vulkan

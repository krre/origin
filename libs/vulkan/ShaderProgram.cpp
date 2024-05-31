#include "ShaderProgram.h"
#include "Renderer.h"
#include "api/descriptor/DescriptorPool.h"
#include "api/descriptor/DescriptorSetLayout.h"
#include "api/descriptor/DescriptorSets.h"
#include "api/pipeline/PipelineLayout.h"
#include <spirv_cross/spirv_cross.hpp>

namespace Vulkan {

ShaderProgram::ShaderProgram(Device* device) : device(device) {
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

            VkWriteDescriptorSet writeDescriptorSet = {};
            writeDescriptorSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
            writeDescriptorSet.dstBinding = binding.layoutBinding.binding;
            writeDescriptorSet.dstArrayElement = 0;
            writeDescriptorSet.descriptorType = binding.layoutBinding.descriptorType;
            writeDescriptorSet.descriptorCount = binding.layoutBinding.descriptorCount;

            writeDescriptorSets[binding.variableName] = writeDescriptorSet;
        }
    }

    // Create descriptor pool
    for (const auto& it : descriptorTypes) {
        descriptorPool->addPoolSize(it.first, it.second);
    }

    if (descriptorPool->getPoolSizeCount()) {
        descriptorPool->setMaxSets(descriptorSetLayouts.size());
        descriptorPool->create();
    }

    // Create descriptor set layouts
    for (const auto& it : descriptorSetLayouts) {
        it.second->create();
        descriptorSets->addDescriptorSetLayout(it.second->getHandle());
        pipelineLayout->addDescriptorSetLayout(it.second->getHandle());
    }

    if (descriptorSets->getCount()) {
        descriptorSets->allocate();
        updateDescriptorSets();
    }

    pipelineLayout->create();
}

Shader::LocationInfo ShaderProgram::getLocationInfo(const std::string& name) const {
    for (const auto& shader : shaders) {
        for (const auto& locationInfo : shader->getLocations()) {
            if (locationInfo.name == name) {
                return locationInfo;
            }
        }
    }

    assert(false);
    return Shader::LocationInfo {};
}

void ShaderProgram::bindBuffer(const std::string& name, VkDescriptorBufferInfo descriptorBufferInfo) {
    descriptorBufferInfos[name] = descriptorBufferInfo;
//    updateDescriptorSets();
}

void ShaderProgram::bindImage(const std::string& name, VkDescriptorImageInfo descriptorImageInfo) {
    descriptorImageInfos[name] = descriptorImageInfo;
//    updateDescriptorSets();
}

void ShaderProgram::updateDescriptorSets() {
    for (const auto& it : writeDescriptorSets) {
        const std::string& name = it.first;
        VkWriteDescriptorSet writeDescriptorSet = it.second;

        for (const auto& it : descriptorBufferInfos) {
            if (it.first == name) {
                writeDescriptorSet.pBufferInfo = &it.second;
                break;
            }
        }

        for (const auto& it : descriptorImageInfos) {
            if (it.first == name) {
                writeDescriptorSet.pImageInfo = &it.second;
                break;
            }
        }

        writeDescriptorSet.dstSet = descriptorSets->at(0); // TODO: Temporary dirty hack

        descriptorSets->addWriteDescriptorSet(writeDescriptorSet);
    }

    descriptorSets->updateDescriptorSets();
}

}

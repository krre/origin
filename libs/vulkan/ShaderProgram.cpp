#include "ShaderProgram.h"
#include "Renderer.h"
#include "api/descriptor/DescriptorPool.h"
#include "api/descriptor/DescriptorSetLayout.h"
#include "api/descriptor/DescriptorSets.h"
#include "api/pipeline/PipelineLayout.h"
#include <spirv_cross/spirv_cross.hpp>

namespace Vulkan {

ShaderProgram::ShaderProgram(Device* device) : m_device(device) {
    m_descriptorPool = std::make_unique<DescriptorPool>(device);
    m_descriptorSets = std::make_unique<DescriptorSets>(device, m_descriptorPool.get());

    m_pipelineLayout = std::make_unique<PipelineLayout>(device);
}

ShaderProgram::~ShaderProgram() {
    m_descriptorSets->destroy();
    m_descriptorPool->destroy();
}

void ShaderProgram::loadShader(const std::string& filePath) {
    std::unique_ptr<Shader> shader = std::make_unique<Shader>();
    shader->load(filePath);
    m_shaders.push_back(std::move(shader));
}

void ShaderProgram::create() {
    std::map<VkDescriptorType, uint32_t> descriptorTypes;

    // Collect descriptor set layouts and descriptor types
    for (const auto& shader : m_shaders) {
        for (const auto& binding : shader->bindings()) {
            if (m_descriptorSetLayouts.find(binding.set) == m_descriptorSetLayouts.end()) {
                m_descriptorSetLayouts[binding.set] = std::make_unique<DescriptorSetLayout>(m_device);
            }

            m_descriptorSetLayouts.at(binding.set)->addLayoutBinding(binding.layoutBinding);

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

            m_writeDescriptorSets[binding.variableName] = writeDescriptorSet;
        }
    }

    // Create descriptor pool
    for (const auto& it : descriptorTypes) {
        m_descriptorPool->addPoolSize(it.first, it.second);
    }

    if (m_descriptorPool->poolSizeCount()) {
        m_descriptorPool->setMaxSets(m_descriptorSetLayouts.size());
        m_descriptorPool->create();
    }

    // Create descriptor set layouts
    for (const auto& it : m_descriptorSetLayouts) {
        it.second->create();
        m_descriptorSets->addDescriptorSetLayout(it.second->handle());
        m_pipelineLayout->addDescriptorSetLayout(it.second->handle());
    }

    if (m_descriptorSets->count()) {
        m_descriptorSets->allocate();
        updateDescriptorSets();
    }

    m_pipelineLayout->create();
}

Shader::LocationInfo ShaderProgram::locationInfo(const std::string& name) const {
    for (const auto& shader : m_shaders) {
        for (const auto& locationInfo : shader->locations()) {
            if (locationInfo.name == name) {
                return locationInfo;
            }
        }
    }

    assert(false);
    return Shader::LocationInfo {};
}

void ShaderProgram::bindBuffer(const std::string& name, VkDescriptorBufferInfo descriptorBufferInfo) {
    m_descriptorBufferInfos[name] = descriptorBufferInfo;
//    updateDescriptorSets();
}

void ShaderProgram::bindImage(const std::string& name, VkDescriptorImageInfo descriptorImageInfo) {
    m_descriptorImageInfos[name] = descriptorImageInfo;
//    updateDescriptorSets();
}

void ShaderProgram::updateDescriptorSets() {
    for (const auto& it : m_writeDescriptorSets) {
        const std::string& name = it.first;
        VkWriteDescriptorSet writeDescriptorSet = it.second;

        for (const auto& it : m_descriptorBufferInfos) {
            if (it.first == name) {
                writeDescriptorSet.pBufferInfo = &it.second;
                break;
            }
        }

        for (const auto& it : m_descriptorImageInfos) {
            if (it.first == name) {
                writeDescriptorSet.pImageInfo = &it.second;
                break;
            }
        }

        writeDescriptorSet.dstSet = m_descriptorSets->at(0); // TODO: Temporary dirty hack

        m_descriptorSets->addWriteDescriptorSet(writeDescriptorSet);
    }

    m_descriptorSets->updateDescriptorSets();
}

}

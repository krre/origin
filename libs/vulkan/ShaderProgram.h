#pragma once
#include "Shader.h"
#include <vulkan/vulkan.h>
#include <map>
#include <vector>

namespace Vulkan {

class Device;
class Shader;
struct LocationInfo;

class PipelineLayout;
class DescriptorSetLayout;
class Buffer;
class DescriptorSets;
class DescriptorPool;

class ShaderProgram {
public:
    ShaderProgram(Device* device);
    ~ShaderProgram();

    void loadShader(const std::string& filePath);
    const std::vector<std::unique_ptr<Shader>>& shaders() const { return m_shaders; }
    void create();

    const DescriptorSets* descriptorSets() const { return m_descriptorSets.get(); }
    const PipelineLayout* pipelineLayout() const { return m_pipelineLayout.get(); }
    Shader::LocationInfo locationInfo(const std::string& name) const;

    void bindBuffer(const std::string& name, VkDescriptorBufferInfo descriptorBufferInfo);
    void bindImage(const std::string& name, VkDescriptorImageInfo descriptorImageInfo);

private:
    void updateDescriptorSets();

    Device* m_device = nullptr;
    std::vector<std::unique_ptr<Shader>> m_shaders;
    std::unique_ptr<PipelineLayout> m_pipelineLayout;
    std::unique_ptr<DescriptorPool> m_descriptorPool;
    std::map<uint32_t, std::unique_ptr<DescriptorSetLayout>> m_descriptorSetLayouts;
    std::unique_ptr<DescriptorSets> m_descriptorSets;
    std::map<std::string, VkDescriptorBufferInfo> m_descriptorBufferInfos;
    std::map<std::string, VkDescriptorImageInfo> m_descriptorImageInfos;
    std::map<std::string, VkWriteDescriptorSet> m_writeDescriptorSets;
    std::vector<VkVertexInputAttributeDescription> m_vertexInputAttributeDescriptions;
};

}

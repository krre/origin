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
    const std::vector<std::unique_ptr<Shader>>& getShaders() const { return shaders; }
    void create();

    const DescriptorSets* getDescriptorSets() const { return descriptorSets.get(); }
    const PipelineLayout* getPipelineLayout() const { return pipelineLayout.get(); }
    Shader::LocationInfo getLocationInfo(const std::string& name) const;

    void bindBuffer(const std::string& name, VkDescriptorBufferInfo descriptorBufferInfo);
    void bindImage(const std::string& name, VkDescriptorImageInfo descriptorImageInfo);

private:
    void updateDescriptorSets();

    Device* device = nullptr;
    std::vector<std::unique_ptr<Shader>> shaders;
    std::unique_ptr<PipelineLayout> pipelineLayout;
    std::unique_ptr<DescriptorPool> descriptorPool;
    std::map<uint32_t, std::unique_ptr<DescriptorSetLayout>> descriptorSetLayouts;
    std::unique_ptr<DescriptorSets> descriptorSets;
    std::map<std::string, VkDescriptorBufferInfo> descriptorBufferInfos;
    std::map<std::string, VkDescriptorImageInfo> descriptorImageInfos;
    std::map<std::string, VkWriteDescriptorSet> writeDescriptorSets;
    std::vector<VkVertexInputAttributeDescription> vertexInputAttributeDescriptions;
};

} // Vulkan

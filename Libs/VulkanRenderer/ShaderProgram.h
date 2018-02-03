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

    struct BufferInfo {
        uint32_t size;
        void* uniform;
        std::shared_ptr<Buffer> buffer;
    };

    ShaderProgram();
    ~ShaderProgram();
    void loadShader(const std::string& filePath);
    const std::vector<std::unique_ptr<Shader>>& getShaders() const { return shaders; }
    void create();

    const DescriptorSets* getDescriptorSets() const { return descriptorSets.get(); }
    const PipelineLayout* getPipelineLayout() const { return pipelineLayout.get(); }
    const Shader::LocationInfo* getLocationInfo(const std::string& name) const;

//    Buffer* getUniformBuffer(const std::string& name) const { return bufferInfos.at(name).buffer.get(); }
    void createPipeline();
    void bindUniform(const std::string& name, uint32_t size, void* uniform = nullptr);
    void bindImage(const std::string& name, VkDescriptorImageInfo descriptorImageInfo);
    void writeUniform(const std::string& name, VkDeviceSize offset = 0, VkDeviceSize size = 0, void* data = nullptr);
    void readUniform(const std::string& name, VkDeviceSize offset = 0, VkDeviceSize size = 0, void* data = nullptr);

private:
    Device* device = nullptr;
    std::vector<std::unique_ptr<Shader>> shaders;
    std::unique_ptr<PipelineLayout> pipelineLayout;
    std::unique_ptr<DescriptorPool> descriptorPool;
    std::map<uint32_t, std::unique_ptr<DescriptorSetLayout>> descriptorSetLayouts;
    std::unique_ptr<DescriptorSets> descriptorSets;
//    std::map<std::string, BufferInfo> bufferInfos;
    std::vector<VkVertexInputAttributeDescription> vertexInputAttributeDescriptions;
//    std::map<std::string, VkDescriptorImageInfo> imageInfos;
};

} // Vulkan

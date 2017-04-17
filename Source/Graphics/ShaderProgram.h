#pragma once
#include "../Core/Object.h"
#include "../Resource/ShaderResource.h"
#include "Vulkan/Descriptor/DescriptorSetLayout.h"
#include "Vulkan/Descriptor/DescriptorSets.h"
#include "Vulkan/Buffer.h"
#include "Vulkan/Image/Image.h"
#include <map>

namespace Vulkan {
    class Device;
    class GraphicsPipeline;
    class PipelineLayout;
}

class ShaderProgram : public Object {

public:

    struct BufferInfo {
        uint32_t size;
        void* uniform;
        std::shared_ptr<Vulkan::Buffer> buffer;
    };

    ShaderProgram(Vulkan::Device* device = nullptr);
    ~ShaderProgram();
    void addShader(const std::string& path);
    Vulkan::GraphicsPipeline* getGraphicsPipeline() { return graphicsPipeline.get(); }
    const Vulkan::DescriptorSetLayout* getDescriptorSetLayout() const { return &descriptorSetLayout; }
    const Vulkan::DescriptorSets* getDescriptorSets() const { return &descriptorSets; }
    const Vulkan::PipelineLayout* getPipelineLayout() const { return pipelineLayout.get(); }
    Vulkan::Buffer* getUniformBuffer(const std::string& name) const { return bufferInfos.at(name).buffer.get(); }
    void createPipeline();
    void createIndexBuffer(VkDeviceSize size);
    int createVertexInputBindingDescription(uint32_t stride, VkVertexInputRate inputRate = VK_VERTEX_INPUT_RATE_VERTEX);
    Vulkan::Buffer* getIndexBuffer() const { return indexBuffer.get(); }
    void linkUniform(const std::string& name, uint32_t size, void* uniform = nullptr);
    void linkImage(const std::string& name, VkDescriptorImageInfo descriptorImageInfo);
    void linkInput(const std::string& name, uint32_t binding, uint32_t offset = 0);
    void writeUniform(const std::string& name, VkDeviceSize offset = 0, VkDeviceSize size = 0, void* data = nullptr);
    void readUniform(const std::string& name, VkDeviceSize offset = 0, VkDeviceSize size = 0, void* data = nullptr);

private:
    const Vulkan::Device* device;
    std::unique_ptr<Vulkan::GraphicsPipeline> graphicsPipeline;
    std::unique_ptr<Vulkan::PipelineLayout> pipelineLayout;
    Vulkan::DescriptorPool descriptorPool;
    std::vector<ShaderResource*> shaderResources;
    std::vector<VkVertexInputBindingDescription> vertexInputBindingDescriptions;
    Vulkan::DescriptorSetLayout descriptorSetLayout;
    Vulkan::DescriptorSets descriptorSets;
    std::map<std::string, BufferInfo> bufferInfos;
    std::map<std::string, VkVertexInputAttributeDescription> inputInfos;
    std::map<std::string, VkDescriptorImageInfo> imageInfos;
    std::shared_ptr<Vulkan::Buffer> indexBuffer;
    int vertexBindingCount = 0;

    VkFormat getFormat(ShaderResource::Input* input);
};

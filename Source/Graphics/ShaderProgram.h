#pragma once
#include "../Core/Object.h"
#include "../Resource/ShaderResource.h"
#include "Vulkan/Device/Device.h"
#include "Vulkan/Descriptor/DescriptorPool.h"
#include "Vulkan/Descriptor/DescriptorSetLayout.h"
#include "Vulkan/Descriptor/DescriptorSets.h"
#include "Vulkan/Pipeline/GraphicsPipeline.h"
#include "Vulkan/Buffer.h"
#include "Vulkan/Image/Image.h"
#include <map>

class ShaderProgram : public Object {

public:

    struct BufferInfo {
        uint32_t size;
        void* uniform;
        std::shared_ptr<Vulkan::Buffer> buffer;
    };

    struct InputInfo {
        VkBufferUsageFlagBits usage;
        uint32_t size;
        bool moveToDevice;
        std::shared_ptr<Vulkan::Buffer> buffer;
        VkVertexInputBindingDescription vertexInputBindingDescription;
        VkVertexInputAttributeDescription vertexInputAttributeDescription;
    };

    ShaderProgram(const Vulkan::Device* device);
    ~ShaderProgram();
    void addShader(const std::string& path);
    Vulkan::GraphicsPipeline* getGraphicsPipeline() { return &graphicsPipeline; }
    const Vulkan::DescriptorSetLayout* getDescriptorSetLayout() const { return &descriptorSetLayout; }
    const Vulkan::DescriptorSets* getDescriptorSets() const { return &descriptorSets; }
    const Vulkan::PipelineLayout* getPipelineLayout() const { return &pipelineLayout; }
    Vulkan::Buffer* getUniformBuffer(const std::string& name) const { return bufferInfos.at(name).buffer.get(); }
    void createPipeline();
    void createIndexBuffer(VkDeviceSize size);
    Vulkan::Buffer* getIndexBuffer() const { return indexBuffer.get(); }
    void linkUniform(const std::string& name, uint32_t size, void* uniform = nullptr);
    void linkImage(const std::string& name, VkDescriptorImageInfo descriptorImageInfo);
    void linkInput(const std::string& name, VkDeviceSize size, VkBufferUsageFlagBits usage, bool moveToDevice);
    void writeUniform(const std::string& name, VkDeviceSize offset = 0, VkDeviceSize size = 0, void* data = nullptr);
    void readUniform(const std::string& name, VkDeviceSize offset = 0, VkDeviceSize size = 0, void* data = nullptr);

private:
    const Vulkan::Device* device;
    Vulkan::GraphicsPipeline graphicsPipeline;
    Vulkan::PipelineLayout pipelineLayout;
    Vulkan::DescriptorPool descriptorPool;
    std::vector<ShaderResource*> shaderResources;
    Vulkan::DescriptorSetLayout descriptorSetLayout;
    Vulkan::DescriptorSets descriptorSets;
    std::map<std::string, BufferInfo> bufferInfos;
    std::map<std::string, InputInfo> inputInfos;
    std::map<std::string, VkDescriptorImageInfo> imageInfos;
    std::shared_ptr<Vulkan::Buffer> indexBuffer;

    VkFormat getFormat(ShaderResource::Input* input);
};

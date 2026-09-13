#pragma once
#include <QVulkanWindowRenderer>
#include <QVulkanFunctions>
#include <cstddef>
#include <glm/glm.hpp>
#include <vulkan/vulkan.h>
#include <vector>

class QVulkanWindow;

class RenderEngine final : public QVulkanWindowRenderer {
public:
    explicit RenderEngine(QVulkanWindow* window);
    ~RenderEngine() override;

    void setVoxelVertices(const void* vertices, uint32_t count, uint32_t byteSize);
    void setLineVertices(const void* vertices, uint32_t count, uint32_t byteSize);
    void updateMvp(const glm::mat4& mvp);
    void updateShadeless(bool shadeless);

    bool isReady() const { return m_device != VK_NULL_HANDLE; }

    void initResources() override;
    void initSwapChainResources() override;
    void releaseSwapChainResources() override;
    void releaseResources() override;
    void startNextFrame() override;

private:
    struct Buffer {
        VkBuffer handle = VK_NULL_HANDLE;
        VkDeviceMemory memory = VK_NULL_HANDLE;
        VkDeviceSize size = 0;
    };

    struct RenderPass {
        VkPipeline pipeline = VK_NULL_HANDLE;
        uint32_t vertexCount = 0;
    };

    struct VoxelUBO {
        glm::mat4 mvp = glm::mat4(1.0f);
        int shadeless = 0;
    } m_voxelUbo;

    struct LineUBO {
        glm::mat4 mvp = glm::mat4(1.0f);
    } m_lineUbo;

    static constexpr uint32_t InitialBufferSize = 1'000'000;

    void createBuffer(Buffer& buffer, VkDeviceSize size, VkBufferUsageFlags usage);
    void destroyBuffer(Buffer& buffer);
    void writeBuffer(const Buffer& buffer, const void* data, VkDeviceSize size);
    void ensureBufferCapacity(Buffer& buffer, VkDeviceSize required, VkBufferUsageFlags usage);
    uint32_t findMemoryType(uint32_t typeBits, VkMemoryPropertyFlags properties) const;
    VkShaderModule createShaderModule(const QString& relativePath) const;
    VkPipeline createPipeline(VkShaderModule vertexShader, VkShaderModule fragmentShader,
                              VkPrimitiveTopology topology, uint32_t stride,
                              const std::vector<VkVertexInputAttributeDescription>& attributes,
                              VkPipelineLayout layout) const;
    void createDescriptors();
    void destroyDescriptors();
    void createPipelines();
    void destroyPipelines();
    void updateCurrentUniforms();
    void recordDraw(VkCommandBuffer commandBuffer, VkPipeline pipeline, VkDescriptorSet descriptorSet,
                    VkBuffer vertexBuffer, uint32_t vertexCount) const;

    QVulkanWindow* m_window;
    VkDevice m_device = VK_NULL_HANDLE;
    VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
    QVulkanDeviceFunctions* m_deviceFunctions = nullptr;
    QVulkanFunctions* m_instanceFunctions = nullptr;
    uint32_t m_frameCount = 0;
    Buffer m_voxelVertices;
    Buffer m_lineVertices;
    std::vector<Buffer> m_voxelUniforms;
    std::vector<Buffer> m_lineUniforms;
    VkDescriptorSetLayout m_voxelDescriptorSetLayout = VK_NULL_HANDLE;
    VkDescriptorSetLayout m_lineDescriptorSetLayout = VK_NULL_HANDLE;
    VkDescriptorPool m_descriptorPool = VK_NULL_HANDLE;
    VkPipelineLayout m_voxelPipelineLayout = VK_NULL_HANDLE;
    VkPipelineLayout m_linePipelineLayout = VK_NULL_HANDLE;
    std::vector<VkDescriptorSet> m_voxelDescriptorSets;
    std::vector<VkDescriptorSet> m_lineDescriptorSets;
    VkShaderModule m_voxelVertexShader = VK_NULL_HANDLE;
    VkShaderModule m_voxelFragmentShader = VK_NULL_HANDLE;
    VkShaderModule m_lineVertexShader = VK_NULL_HANDLE;
    VkShaderModule m_lineFragmentShader = VK_NULL_HANDLE;
    std::vector<std::byte> m_voxelVertexData;
    std::vector<std::byte> m_lineVertexData;
    RenderPass m_voxelRenderPass;
    RenderPass m_lineRenderPass;
};

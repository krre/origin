#pragma once
#include "OctreeRenderer.h"
#include <glm/glm.hpp>
#include <memory>

namespace Vulkan {
    class GpuBuffer;
    class ShaderProgram;
    class GraphicsPipeline;
}

class RaycastOctreeRenderer : public OctreeRenderer {
public:
    struct UBO {
        glm::vec4 backgroundColor = glm::vec4(1.0, 1.0, 1.0, 1.0);
        glm::vec4 lightColor = glm::vec4(1.0, 1.0, 1.0, 1.0);
        glm::vec4 lightPos = glm::vec4(1.0, 1.0, 1.0, 1.0);

        int shadeless = 1;
        int frameWidth = 0;
        int frameHeight = 0;

        float ambientStrength = 1.0;
        float lod = 1.0;
    };

    struct MetaData {
        glm::vec3 origin;
        glm::vec3 startCorner;
        glm::vec3 stepW;
        glm::vec3 stepH;
        glm::uint blockIndex;
    };

    RaycastOctreeRenderer(Object* parent = nullptr);
    ~RaycastOctreeRenderer();

    void writeCommandBuffer(Vulkan::CommandBuffer* commandBuffer, Vulkan::Framebuffer* framebuffer) override;
    void draw() override;
    void drawView(View3D* view) override;

    void writeUBO(const UBO& ubo);
    void writeBlocks(uint32_t offset, void* data, uint32_t size);
    void writeMeta(uint32_t offset, void* data, uint32_t size);

private:
    std::unique_ptr<Vulkan::GpuBuffer> m_vertexBuffer;
    std::unique_ptr<Vulkan::GpuBuffer> m_uboBuffer;
    std::unique_ptr<Vulkan::GpuBuffer> m_blocksBuffer;
    std::unique_ptr<Vulkan::GpuBuffer> m_metaBuffer;
    std::unique_ptr<Vulkan::ShaderProgram> m_shaderProgram;
    std::unique_ptr<Vulkan::GraphicsPipeline> m_graphicsPipeline;
    uint32_t m_vertextCount = 0;
    std::vector<uint32_t> m_blocks;
};

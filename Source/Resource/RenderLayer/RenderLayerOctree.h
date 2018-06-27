#pragma once
#include "RenderLayer.h"
#include <glm/glm.hpp>

namespace Vulkan {
    class GpuBuffer;
    class ShaderProgram;
    class GraphicsPipeline;
}

namespace Origin {

class RenderLayerOctree : public RenderLayer {

public:

    struct UBO {
        glm::vec4 backgroundColor = glm::vec4(1.0, 1.0, 1.0, 1.0);
        glm::vec4 lightColor = glm::vec4(1.0, 1.0, 1.0, 1.0);
        glm::vec4 lightPos = glm::vec4(1.0, 1.0, 1.0, 1.0);

        int shadeless = 1;
        int frameWidth = 100;
        int frameHeight = 100;

        float ambientStrength = 1.0;
        float lod = 1.0;
    };

    RenderLayerOctree(Vulkan::Device* device, Object* parent = nullptr);
    ~RenderLayerOctree();

    void write(Vulkan::CommandBuffer* commandBuffer, Vulkan::Framebuffer* framebuffer) override;
    Vulkan::GpuBuffer* getVertexBuffer() const { return vertexBuffer.get(); }

    void writeUBO(const UBO& ubo);

private:
    std::unique_ptr<Vulkan::GpuBuffer> vertexBuffer;
    std::unique_ptr<Vulkan::GpuBuffer> uboBuffer;
    std::unique_ptr<Vulkan::ShaderProgram> shaderProgram;
    std::unique_ptr<Vulkan::GraphicsPipeline> graphicsPipeline;
    uint32_t vertextCount = 0;
};

} // Origin

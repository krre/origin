#pragma once
#include "Renderer.h"
#include "ECS/Scenes/Scene.h"
#include "Octree/Octree.h"

namespace Vulkan {
    class GpuBuffer;
    class ShaderProgram;
    class GraphicsPipeline;
}

namespace Origin {

class SceneRenderer : public Renderer {

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

    SceneRenderer(Object* parent = nullptr);
    ~SceneRenderer();

    void writeCommandBuffer(Vulkan::CommandBuffer* commandBuffer, Vulkan::Framebuffer* framebuffer) override;

    void writeUBO(const UBO& ubo);
    void writeBlocks(uint32_t offset, void* data, uint32_t size);
    void writeMeta(uint32_t offset, void* data, uint32_t size);

    static SceneRenderer* get();

    void draw() override;
    bool getActive() const override;

    void addScene(Scene* scene);
    void clearScenes();

private:
    std::unique_ptr<Vulkan::GpuBuffer> vertexBuffer;
    std::unique_ptr<Vulkan::GpuBuffer> uboBuffer;
    std::unique_ptr<Vulkan::GpuBuffer> blocksBuffer;
    std::unique_ptr<Vulkan::GpuBuffer> metaBuffer;
    std::unique_ptr<Vulkan::ShaderProgram> shaderProgram;
    std::unique_ptr<Vulkan::GraphicsPipeline> graphicsPipeline;
    uint32_t vertextCount = 0;

    std::vector<Scene*> scenes;
    std::vector<uint32_t> blocks;
};

} // Origin

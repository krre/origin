#pragma once
#include "../Core/Singleton.h"
#include "../Scene/Scene2D.h"
#include "../Event/Event.h"
#include "../Graphics/Vulkan/Pipeline/PipelineCache.h"
#include "../Graphics/ShaderProgram.h"
#include "../Graphics/Vulkan/Sampler.h"
#include "../Graphics/Vulkan/RenderPass.h"
#include "../UI/Text/Font.h"

const int MAX_CHAR_COUNT = 2048;

class Label;

class DebugHUD : public Singleton<DebugHUD>, public Scene2D {

    struct UBO {
        glm::mat4 projection = glm::mat4(1.0);
        glm::mat4 model = glm::mat4(1.0);
    } ubo;

public:
    DebugHUD();
    ~DebugHUD();
    void init() override;
    void update(float dt) override;
    void trigger();

private:
    void create();
    void writeCommands(Vulkan::CommandBuffer* commandBuffer) override;

    Vulkan::PipelineCache pipelineCache;
    Vulkan::RenderPass renderPass;
    std::unique_ptr<Vulkan::Buffer> vertexBuffer;
    ShaderProgram shaderProgram;
    Vulkan::Sampler sampler;
    Font* font;
    float accumTime = 0.5;
    int counter = 30;
    int fps = 0;
    std::string vulkanApiVersion;
    std::shared_ptr<Label> displayLabel;
};

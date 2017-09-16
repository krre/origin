#pragma once
#include "Core/Singleton.h"
#include "Scene/Scene2D.h"
#include "Graphics/Render/Vulkan/Wrapper/Pipeline/PipelineCache.h"
#include "Graphics/ShaderProgram.h"
#include "Graphics/Render/Vulkan/Wrapper/Sampler.h"
#include "Graphics/Render/Vulkan/Wrapper/RenderPass.h"

const int MAX_CHAR_COUNT = 2048;

class Label;
class Font;

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
    void onWindowResize(int width, int height) override;

    Vulkan::PipelineCache pipelineCache;
    Vulkan::RenderPass renderPass;
    ShaderProgram shaderProgram;
    Vulkan::Sampler sampler;
    Font* font;
    float accumTime = 0.5;
    int counter = 30;
    int fps = 0;
    std::string vulkanApiVersion;
    std::shared_ptr<Label> displayLabel;
};

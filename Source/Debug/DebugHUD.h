#pragma once
#include "Core/Singleton.h"
#include "UI/View2D.h"
#include "Graphics/Vulkan/Pipeline/PipelineCache.h"
#include "Graphics/ShaderProgram.h"
#include "Graphics/Vulkan/Sampler.h"
#include "Graphics/Vulkan/RenderPass.h"
#include <glm/glm.hpp>

const int MAX_CHAR_COUNT = 2048;

class Label;
class Font;

class DebugHUD : public Singleton<DebugHUD>, public View2D {

    struct UBO {
        glm::mat4 projection = glm::mat4(1.0);
        glm::mat4 model = glm::mat4(1.0);
    } ubo;

public:
    DebugHUD();
    ~DebugHUD();
    void update(float dt);
    void trigger();

private:
    void create();
//    void writeCommands(Vulkan::CommandBuffer* commandBuffer) override;
//    void onWindowResize(int width, int height) override;

//    Vulkan::PipelineCache pipelineCache;
//    Vulkan::RenderPass renderPass;
//    ShaderProgram shaderProgram;
//    Vulkan::Sampler sampler;
    Font* font;
    float accumTime = 0.5;
    int counter = 30;
    int fps = 0;
    std::string vulkanApiVersion;
    std::shared_ptr<Label> displayLabel;
};

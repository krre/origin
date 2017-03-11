#pragma once
#include "../Core/Singleton.h"
#include "../Scene/Scene2D.h"
#include "../UI/Label.h"
#include "../UI/LinearLayout.h"
#include "../Event/Event.h"
#include "../Graphics/Vulkan/Pipeline/GraphicsPipeline.h"
#include "../Graphics/Vulkan/Pipeline/PipelineLayout.h"
#include "../Graphics/Vulkan/Pipeline/PipelineCache.h"
#include "../Graphics/Vulkan/Buffer.h"
#include "../Graphics/Vulkan/Sampler.h"
#include "../Graphics/Vulkan/Image/ImageView.h"
#include "../Graphics/Vulkan/Image/Image.h"
#include "../Graphics/ShaderProgram/TextShaderProgram.h"

const int MAX_CHAR_COUNT = 2048;

class DebugHUD : public Singleton<DebugHUD>, public Scene2D {

public:
    DebugHUD();
    ~DebugHUD();
    void init() override;
    void draw(float dt) override;
    void update(float dt) override;
    void create() override;
    void trigger();

private:
    void buildCommandBuffers() override;

    Vulkan::PipelineLayout pipelineLayout;
    Vulkan::PipelineCache pipelineCache;
    Vulkan::RenderPass renderPass;
    Vulkan::GraphicsPipeline graphicsPipeline;
    Vulkan::Buffer* vertexBuffer = nullptr;
    Vulkan::Sampler sampler;
    Vulkan::ImageView* samplerImageView = nullptr;
    Vulkan::Image* samplerImage = nullptr;
    TextShaderProgram tsp;

    Label fps;
    Label version;
    Label vulkan;
    Label vendor;
    Label cpuCount;
    Label systemRAM;
    Label posX;
    Label posY;
    Label posZ;
    float accumTime = 0.5;
    int counter = 30;
    uint32_t numLetters = 0;
    std::shared_ptr<LinearLayout> statisticsLayout = std::make_shared<LinearLayout>(LinearLayout::VERICAL);
};

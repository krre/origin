#pragma once
#include "../Core/Singleton.h"
#include "../Scene/Scene2D.h"
#include "../UI/Text.h"
#include "../UI/LinearLayout.h"
#include "../Event/Event.h"
#include "../Graphics/Vulkan/Pipeline/GraphicsPipeline.h"
#include "../Graphics/Vulkan/Pipeline/PipelineLayout.h"
#include "../Graphics/Vulkan/Pipeline/PipelineCache.h"
#include "../Graphics/Vulkan/Descriptor/DescriptorSetLayout.h"
#include "../Graphics/Vulkan/Descriptor/DescriptorSets.h"
#include "../Graphics/Vulkan/Buffer.h"
#include "../Graphics/Vulkan/Descriptor/DescriptorPool.h"
#include "../Graphics/Vulkan/Descriptor/Descriptor.h"
#include "../Graphics/Vulkan/Sampler.h"

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
    Vulkan::DescriptorPool descriptorPool;
    Vulkan::DescriptorSetLayout descriptorSetLayout;
    Vulkan::DescriptorSets* descriptorSets = nullptr;
    Vulkan::PipelineCache pipelineCache;
    Vulkan::GraphicsPipeline graphicsPipeline;
    Vulkan::Buffer* vertexBuffer = nullptr;
    Vulkan::Buffer* indexBuffer = nullptr;
    Vulkan::Descriptor* uniformVert = nullptr;
    Vulkan::Descriptor* uniformFrag = nullptr;
    Vulkan::Sampler sampler;

    Text fps;
    Text version;
    Text vulkan;
    Text vendor;
    Text cpuCount;
    Text systemRAM;
    Text posX;
    Text posY;
    Text posZ;
    float accumTime = 0.5;
    int counter = 30;
    uint32_t numLetters;
    std::shared_ptr<LinearLayout> statisticsLayout = std::make_shared<LinearLayout>(LinearLayout::VERICAL);
};

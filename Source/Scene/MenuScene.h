#pragma once
#include "Scene2D.h"
#include "../UI/Button.h"
#include "../UI/LinearLayout.h"
#include "../Graphics/Vulkan/Pipeline.h"
#include "../Graphics/Vulkan/PipelineLayout.h"
#include "../Graphics/Vulkan/DescriptorSetLayout.h"
#include "../Graphics/Vulkan/Collection/DescriptorSetCollection.h"
#include "../Graphics/Vulkan/Buffer.h"
#include "../Graphics/Vulkan/DeviceMemory.h"

class MenuScene : public Scene2D {

public:
    MenuScene(int width, int height);
    ~MenuScene();
    void draw(float dt) override;
    void update(float dt) override;
    void create() override;

private:
    void onKeyPressed(const SDL_KeyboardEvent& event) override;
    Vulkan::PipelineLayout* pipelineLayout;
    Vulkan::DescriptorSetLayout* descriptorSetLayout;
    Vulkan::DescriptorSetCollection* descriptorSetCollection = nullptr;
    Vulkan::Pipeline* graphicsPipeline;
    Vulkan::Buffer* vertexBuffer;
    Vulkan::DeviceMemory* vertexMemory;
};

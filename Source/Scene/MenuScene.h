#pragma once
#include "Scene2D.h"
#include "../UI/Button.h"
#include "../UI/LinearLayout.h"
#include "../Graphics/Vulkan/Pipeline.h"
#include "../Graphics/Vulkan/PipelineLayout.h"
#include "../Graphics/Vulkan/Device.h"
#include "../Graphics/Vulkan/DescriptorSetLayout.h"

class MenuScene : public Scene2D {

public:
    MenuScene(int width, int height);
    ~MenuScene();
    void draw(float dt) override;
    void update(float dt) override;

private:
    void onKeyPressed(const SDL_KeyboardEvent& event);
    Vulkan::PipelineLayout* pipelineLayout;
    Vulkan::DescriptorSetLayout* descriptorSetLayout;
    Vulkan::Pipeline* graphicsPipeline;
    Vulkan::Device* device;
};

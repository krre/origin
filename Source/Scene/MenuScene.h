#pragma once
#include "Scene2D.h"
#include "../UI/Button.h"
#include "../UI/LinearLayout.h"
#include "../Graphics/Vulkan/Pipeline/GraphicsPipeline.h"
#include "../Graphics/Vulkan/Pipeline/PipelineLayout.h"
#include "../Graphics/Vulkan/Descriptor/DescriptorSetLayout.h"
#include "../Graphics/Vulkan/Descriptor/DescriptorSets.h"
#include "../Graphics/Vulkan/Buffer.h"
#include "../Graphics/Vulkan/Descriptor/DescriptorPool.h"
#include "../Graphics/Vulkan/Descriptor/Descriptor.h"

class MenuScene : public Scene2D {

    struct UBOvert {
        glm::mat4 mvp = glm::mat4(1.0);
    } uboVert;

    struct UBOfrag {
        glm::vec3 color = glm::vec3(1.0, 0.0, 0.0);
    } uboFrag;

public:
    MenuScene();
    ~MenuScene();
    void init() override;
    void draw(float dt) override;
    void update(float dt) override;
    void create() override;

private:
    void onKeyPressed(const SDL_KeyboardEvent& event) override;
    void buildCommandBuffers() override;

    Vulkan::PipelineLayout* pipelineLayout = nullptr;
    Vulkan::DescriptorPool* descriptorPool = nullptr;
    Vulkan::DescriptorSetLayout* descriptorSetLayout = nullptr;
    Vulkan::DescriptorSets* descriptorSets = nullptr;
    Vulkan::GraphicsPipeline* graphicsPipeline = nullptr;
    Vulkan::Buffer* vertexBuffer = nullptr;
    Vulkan::Buffer* indexBuffer = nullptr;
    Vulkan::Descriptor* uniformVert = nullptr;
    Vulkan::Descriptor* uniformFrag = nullptr;
    Plane plane;
};

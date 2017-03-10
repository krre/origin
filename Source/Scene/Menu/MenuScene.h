#pragma once
#include "../Scene2D.h"
#include "MenuShaderProgram.h"
#include "../../UI/Button.h"
#include "../../UI/LinearLayout.h"
#include "../../Graphics/Vulkan/Pipeline/GraphicsPipeline.h"
#include "../../Graphics/Vulkan/Pipeline/PipelineLayout.h"
#include "../../Graphics/Vulkan/Buffer.h"

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

    Vulkan::PipelineLayout pipelineLayout;
    Vulkan::GraphicsPipeline graphicsPipeline;
    Vulkan::Buffer* vertexBuffer = nullptr;
    Vulkan::Buffer* indexBuffer = nullptr;
    Plane plane;
    MenuShaderProgram msp;
};

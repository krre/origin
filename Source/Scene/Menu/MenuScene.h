#pragma once
#include "Scene/Scene2D.h"
#include "Graphics/ShaderProgram.h"
#include "Graphics/Plane.h"

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
    void update(float dt) override;

private:
    void create();
    void writeCommands(Vulkan::CommandBuffer* commandBuffer) override;
    void onKeyPressed(const SDL_KeyboardEvent& event) override;

    Plane plane;
    ShaderProgram shaderProgram;
};

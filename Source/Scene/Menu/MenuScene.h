#pragma once
#include "Scene/Scene2D.h"
#include <glm/glm.hpp>

namespace Origin {

class Plane;
class ShaderProgram;

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
    void update(float dt);

private:
    void create();
//    void writeCommands(Vulkan::CommandBuffer* commandBuffer) override;
    void onKeyPressed(const SDL_KeyboardEvent& event) override;

    std::unique_ptr<Plane> plane;
//    std::unique_ptr<ShaderProgram> shaderProgram;
};

} // Origin

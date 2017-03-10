#pragma once
#include "ShaderProgram.h"
#include <glm/glm.hpp>

class BaseShaderProgram : public ShaderProgram {

public:
    friend class MenuScene;

    struct UBOvert {
        glm::mat4 mvp = glm::mat4(1.0);
    } uboVert;

    struct UBOfrag {
        glm::vec3 color = glm::vec3(1.0, 0.0, 0.0);
    } uboFrag;

    BaseShaderProgram(const Vulkan::Device* device);
};

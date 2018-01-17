#pragma once
#include "Core/Common.h"

namespace Origin {

class ShaderProgram;

class RenderState {

public:

    enum class Type {
        Shape2D,
        FreeTypeText,
        SdfText,
        Voxel
    };

    RenderState();
    ~RenderState();
    void setShaderProgram(ShaderProgram* shaderProgram);

private:
    ShaderProgram* shaderProgram;
};

} // Origin

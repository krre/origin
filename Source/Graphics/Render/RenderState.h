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
    void setBlendEnable(bool blendEnable);
    virtual void create() = 0;

protected:
    ShaderProgram* shaderProgram;
    bool blendEnable = false;
};

} // Origin

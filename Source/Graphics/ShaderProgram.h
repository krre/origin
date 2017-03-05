#pragma once
#include "../Core/Object.h"

class ShaderProgram : public Object {

public:

    enum class Type {
        VERTEX,
        FRAGMENT,
        COMPUTE
    };

    ShaderProgram();
    void addShader(const std::string& path);
};

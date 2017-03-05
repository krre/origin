#pragma once
#include "../Core/Object.h"

class ShaderProgram : public Object {

public:
    ShaderProgram();
    void addShader(const std::string& path);
};

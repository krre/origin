#pragma once
#include "../Core/Object.h"
#include "../Resource/ShaderResource.h"
#include <map>

class ShaderProgram : public Object {

public:

    enum class Type {
        VERTEX,
        FRAGMENT,
        COMPUTE
    };

    ShaderProgram();
    void addShader(const std::string& path);

protected:
    std::map<Type, ShaderResource*> shaderResources;
};

#pragma once
#include "Core/Object.h"

namespace Origin {

class ShaderProgram : public Object {

public:

    enum class ShaderType {
        Vertex,
        Fragment
    };

    ShaderProgram();
    ~ShaderProgram();

    virtual void addShader(ShaderType type, const std::string& name) = 0;

private:

};

} // Origin

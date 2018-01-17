#pragma once
#include "Resource/Resource.h"

namespace Origin {

class ShaderProgram : public Resource {

public:

    enum class ShaderType {
        Vertex,
        Fragment
    };

    ShaderProgram();
    ~ShaderProgram();

protected:
    virtual void addShader(ShaderType type, const std::string& name) = 0;
    virtual void create() = 0;

private:

};

} // Origin

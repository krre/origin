#pragma once
#include "Core/Common.h"
#include <experimental/filesystem>

namespace Origin {

namespace fs = std::experimental::filesystem;

class ShaderProgram {

public:

    enum class ProgamType {
        Base,
        Sdf,
        Voxel
    };

    enum class ShaderType {
        Vertex,
        Fragment
    };

    ShaderProgram(const std::string& name);
    ~ShaderProgram();

protected:
    std::map<ShaderType, std::vector<fs::path>> files;
};

} // Origin

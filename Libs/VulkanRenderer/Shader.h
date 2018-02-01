#pragma once
#include <vector>
#include <string>

namespace Vulkan {

class Shader {

public:
    Shader();
    ~Shader();
    void load(const std::string& filePath);

private:
    void analyze();

    std::vector<uint32_t> code;
};

} // Vulkan

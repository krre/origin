#include "ShaderResource.h"
#include <fstream>

ShaderResource::ShaderResource() {

}

void ShaderResource::load(const std::string& path) {
    std::ifstream file(path, std::ios::ate | std::ios::binary);

    if (!file.is_open()) {
        ERROR("Failed to open file: " << path);
    }

    size_t fileSize = (size_t)file.tellg();
    buffer.resize(fileSize / sizeof(uint32_t));

    file.seekg(0);
    file.read(reinterpret_cast<char*>(buffer.data()), fileSize);

    file.close();
}

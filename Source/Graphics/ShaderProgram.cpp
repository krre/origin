#include "ShaderProgram.h"
#include "../Resource/ShaderResource.h"
#include "../Resource/ResourceManager.h"

ShaderProgram::ShaderProgram() {

}

void ShaderProgram::addShader(const std::string& path) {
    PRINT(path)
    ShaderResource* shaderResource = ResourceManager::get()->load<ShaderResource>(path);
}

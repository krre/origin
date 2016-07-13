#include "ShaderGroup.h"

ShaderGroup::ShaderGroup() :
    vertShader(GL_VERTEX_SHADER),
    fragShader(GL_FRAGMENT_SHADER) {
}

void ShaderGroup::setVertShaderPath(const std::string& path) {
    vertShaderPath = path;
}

void ShaderGroup::setFragShaderPath(const std::string& path) {
    fragShaderPath = path;
}


void ShaderGroup::load() {
    vertShader.load(vertShaderPath);
    fragShader.load(fragShaderPath);

    program.addShader(vertShader);
    program.addShader(fragShader);
    program.link();
}

void ShaderGroup::use() {
    program.use();
}

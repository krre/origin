#include "ShaderGroup.h"

ShaderGroup::ShaderGroup() {
}

void ShaderGroup::loadShader(GLenum type, const std::string& path) {
    Shader shader(type);
    shader.load(path);
    program.addShader(shader);
}

void ShaderGroup::link() {
    program.link();
}

void ShaderGroup::bind() {
    program.bind();
}

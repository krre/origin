#include "Effect.h"

Effect::Effect() :
    vertShader(GL_VERTEX_SHADER),
    fragShader(GL_FRAGMENT_SHADER) {
}

void Effect::setVertShaderPath(const std::string& path) {
    vertShaderPath = path;
}

void Effect::setFragShaderPath(const std::string& path) {
    fragShaderPath = path;
}


void Effect::load() {
    vertShader.load(vertShaderPath);
    fragShader.load(fragShaderPath);

    program.addShader(vertShader);
    program.addShader(fragShader);
    program.link();
}

void Effect::use() {
    program.use();
}

#include "Shader.h"
#include "../../Core/App.h"
#include <fstream>

Shader::Shader(GLenum type) : type(type) {

}

bool Shader::load(const std::string& path) {
    this->type = type;
    std::string shaderPath = App::getAbsolutePath() + "/" + folder + "/" + path;
    std::ifstream file(shaderPath);
    if (!file.is_open()) {
        error("Failed open file: " << shaderPath);
        return false;
    }

    source = std::string((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
    id = glCreateShader(type);

    const char *c_str = source.c_str();
    glShaderSource(id, 1, &c_str, NULL);

    glCompileShader(id);
    GLint compiled;
    glGetShaderiv(id, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
        GLsizei len;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
        GLchar* log = new GLchar[len + 1];
        glGetShaderInfoLog(id, len, &len, log);
        error("Shader compilation failed " << log);
        delete[] log;
        glDeleteShader(id);
        return false;
    }

    return true;
}

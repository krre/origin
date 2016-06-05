#include "Shader.h"
#include "../../Core/App.h"
#include <fstream>

extern App* app;

Shader::Shader() {

}

bool Shader::load(const string& path, GLenum type) {
    string shaderPath = app->getAbsolutePath() + "/" + folder + "/" + path;
    ifstream file(shaderPath);
    if (!file.is_open()) {
        cerr << "Failed open file: " << shaderPath << endl;
        return false;
    }

    source = string((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
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
        cerr << "Shader compilation failed " << log << endl;
        delete[] log;
        glDeleteShader(id);
        return false;
    }

    return true;
}

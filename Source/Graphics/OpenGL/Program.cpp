#include "Program.h"

Program::Program() {
    id = glCreateProgram();
}

void Program::addShader(const Shader& shader) {
    glAttachShader(id, shader.getId());
    shaders.push_back(shader.getId());
}

bool Program::link() {
    glLinkProgram(id);
    GLint linked;
    glGetProgramiv(id, GL_LINK_STATUS, &linked);
    if (!linked) {
        GLsizei len;
        glGetProgramiv(id, GL_INFO_LOG_LENGTH, &len);
        GLchar* log = new GLchar[len + 1];
        glGetProgramInfoLog(id, len, &len, log);
        cerr << "Shader linking failed " << log << endl;
        delete[] log;
        for (auto it: shaders) {
            glDeleteShader(it);
        }
        shaders.clear();
        return false;
    }
    return true;
}

void Program::use(bool value) {
    if (value) {
        glUseProgram(id);
    } else {
        glDeleteProgram(id);
    }
}

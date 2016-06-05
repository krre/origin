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
        std::cerr << "Failed open file: " << shaderPath << endl;
        return false;
    }

    source = string((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
    id = glCreateShader(type);
    print("id " << id);

    return true;
}

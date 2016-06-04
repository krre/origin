#include "Shader.h"
#include "../../Core/App.h"
#include <fstream>

extern App* app;

Shader::Shader() {

}

bool Shader::load(const string& path) {
    string shaderPath = app->getAbsolutePath() + "/" + folder + "/" + path;
    ifstream file(shaderPath);
    if (file.is_open()) {
        source = string((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
        return true;
    } else {
        std::cerr << "Failed open file: " << shaderPath << endl;
        return false;
    }
}

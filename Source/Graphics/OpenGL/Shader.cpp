#include "Shader.h"
#include "../../Core/App.h"

extern App* app;

Shader::Shader() {

}

void Shader::load(const string& path) {
    string shaderPath = app->getAbsolutePath() + "/" + folder + "/" + path;
    print(shaderPath);
}

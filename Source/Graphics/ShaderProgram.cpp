#include "ShaderProgram.h"
#include "Resource/ResourceManager.h"
#include "Core/Utils.h"

namespace Origin {

ShaderProgram::ShaderProgram(const std::string& name) {
    std::string shaderDirPath = ResourceManager::getDataPath() + "/Shader";

    for (auto& filePath : fs::directory_iterator(shaderDirPath)) {
        std::string fileName = filePath.path().filename().string();
        std::vector<std::string> words = Utils::split(fileName, '.');
        if (words.at(0) == name) { // base name
            if (words.at(1) == "vert") { // first extension
                files[ShaderType::Vertex].push_back(filePath);
            } else if (words.at(1) == "frag") {
                files[ShaderType::Fragment].push_back(filePath);
            }
        }
    }
}

ShaderProgram::~ShaderProgram() {

}

} // Origin

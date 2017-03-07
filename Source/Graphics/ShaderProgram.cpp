#include "ShaderProgram.h"
#include "../Resource/ResourceManager.h"
#include "../Core/Utils.h"
#include "SpirvParser.h"

ShaderProgram::ShaderProgram() {

}

void ShaderProgram::addShader(const std::string& path) {
    // Template of shader filename: name.type.spv (e.g. Voxel.frag.spv)
    std::vector<std::string> words = Utils::split(path, '.');
    std::string type = words.at(words.size() - 2);
    Type enumType;
    if (type == "vert") {
        enumType = Type::VERTEX;
    } else if (type == "frag") {
        enumType = Type::FRAGMENT;
    } else if (type == "comp") {
        enumType = Type::COMPUTE;
    }
    shaderResources[enumType] = ResourceManager::get()->load<ShaderResource>(path);
}

void ShaderProgram::createDescriptors() {
    SpirvParser parser;

    for (auto it : shaderResources) {
        ShaderResource* shaderResource = it.second;
        parser.parse(shaderResource->getData(), shaderResource->getSize());

        for (auto& descriptor : parser.descriptors) {
            PRINT(descriptor.name << " location: " << descriptor.location  << " descriptorSet: " << descriptor.descriptorSet << " binding: " << descriptor.binding)
        }
    }
}

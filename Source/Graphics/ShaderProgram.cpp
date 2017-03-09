#include "ShaderProgram.h"
#include "../Resource/ResourceManager.h"
#include "../Core/Utils.h"
#include "SpirvParser.h"

using namespace Vulkan;

ShaderProgram::ShaderProgram(const Device* device) :
    device(device),
    descriptorPool(device),
    descriptorSetLayout(device),
    descriptorSets(device, &descriptorPool) {

}

ShaderProgram::~ShaderProgram() {
    descriptorSets.destroy();
    descriptorPool.destroy();
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
        parser.dumpDescriptors();
    }
}

void ShaderProgram::link(std::string name, UniformBuffer* uniformBuffer, uint32_t size) {
    PRINT(name << " " << uniformBuffer << " " << size);
}

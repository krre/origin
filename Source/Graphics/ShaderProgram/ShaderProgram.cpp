#include "ShaderProgram.h"
#include "../../Resource/ResourceManager.h"
#include "../../Core/Utils.h"
#include "../SpirvParser.h"

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
    std::map<VkDescriptorType, uint32_t> descriptorsTypes;
    int vertexBindingCount = 0;

    for (auto& shaderIt : shaderResources) {
        ShaderResource* shaderResource = shaderIt.second;
        parser.parse(shaderResource->getData(), shaderResource->getSize());
//        parser.dumpDescriptors();
//        parser.dumpInputs();

        for (auto& descriptorIt : parser.descriptors) {
            SpirvParser::Descriptor* descriptor = &descriptorIt.second;
            if (descriptorsTypes.find(descriptor->descriptorType) == descriptorsTypes.end()) {
                descriptorsTypes[descriptor->descriptorType] = 1;
            } else {
                descriptorsTypes[descriptor->descriptorType]++;
            }

            VkDescriptorSetLayoutBinding layoutBinding = {};
            layoutBinding.binding = descriptor->binding;
            layoutBinding.descriptorCount = 1;
            layoutBinding.descriptorType = descriptor->descriptorType;
            if (shaderIt.first == Type::VERTEX) {
                layoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
            } else if (shaderIt.first == Type::FRAGMENT) {
                layoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
            }

            descriptorSetLayout.addLayoutBinding(layoutBinding);

            VkWriteDescriptorSet descriptorWrite = {};
            descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
            descriptorWrite.dstBinding = layoutBinding.binding;
            descriptorWrite.dstArrayElement = 0;
            descriptorWrite.descriptorType = layoutBinding.descriptorType;
            descriptorWrite.descriptorCount = layoutBinding.descriptorCount;

            const auto& bufferIt = bufferInfos.find(descriptorIt.first);
            if (bufferIt != bufferInfos.end()) {
                VkBufferUsageFlagBits usage;
                if (descriptor->descriptorType == VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER) {
                    usage = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
                } else if (descriptor->descriptorType == VK_DESCRIPTOR_TYPE_STORAGE_BUFFER) {
                    usage = VK_BUFFER_USAGE_STORAGE_BUFFER_BIT;
                }
                BufferInfo* bufferInfo = &bufferIt->second;
                std::shared_ptr<Buffer> buffer = std::make_shared<Buffer>(device, usage, bufferInfo->size);
                buffer->create();
                buffers.push_back(buffer);
                bufferInfo->buffer = buffer.get();
                descriptorWrite.pBufferInfo = &buffer->descriptorInfo;
                descriptorSets.addWriteDescriptorSet(descriptorWrite);
            }

            const auto& imageIt = imageInfos.find(descriptorIt.first);
            if (imageIt != imageInfos.end()) {
                descriptorWrite.pImageInfo = &imageIt->second;
                descriptorSets.addWriteDescriptorSet(descriptorWrite);
            }
        }

        for (auto& inputIt : parser.inputs) {
            const auto& inputInfoIt = inputInfos.find(inputIt.first);
            if (inputInfoIt != inputInfos.end()) {
                SpirvParser::Input* input = &inputIt.second;
                InputInfo* inputInfo = &inputInfoIt->second;
                if (input->variableType == "OpTypeVector") {

                }
            }
        }
    }

    descriptorSetLayout.create();
    descriptorSets.addDescriptorSetLayout(descriptorSetLayout.getHandle());

    // Descriptor pool
    for (auto& it : descriptorsTypes) {
        descriptorPool.addPoolSize(it.first, it.second);
    }

    descriptorPool.create();
    descriptorSets.allocate();
    descriptorSets.writeDescriptors();
}

void ShaderProgram::linkBuffer(const std::string& name, uint32_t size, void* uniform) {
    BufferInfo linkInfo = {};
    linkInfo.size = size;
    linkInfo.uniform = uniform;
    bufferInfos[name] = linkInfo;
}

void ShaderProgram::linkImage(const std::string& name, VkDescriptorImageInfo descriptorImageInfo) {
    imageInfos[name] = descriptorImageInfo;
}

void ShaderProgram::linkInput(const std::string& name, VkDeviceSize size, Buffer::Type type, Buffer::Destination destination) {
    InputInfo inputInfo = {};
    inputInfo.size = size;
    inputInfo.type = type;
    inputInfo.destination = destination;
    inputInfos[name] = inputInfo;
}

void ShaderProgram::write(const std::string& name, VkDeviceSize offset, VkDeviceSize size, void* data) {
    bufferInfos.at(name).buffer->write(offset, size ? size : bufferInfos.at(name).size, data != nullptr ? data : bufferInfos.at(name).uniform);
}

void ShaderProgram::read(const std::string& name, VkDeviceSize offset, VkDeviceSize size, void* data) {
    bufferInfos.at(name).buffer->read(offset, size ? size : bufferInfos.at(name).size, data != nullptr ? data : bufferInfos.at(name).uniform);
}


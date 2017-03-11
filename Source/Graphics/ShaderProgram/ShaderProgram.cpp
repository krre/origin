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

    for (auto& shaderIt : shaderResources) {
        ShaderResource* shaderResource = shaderIt.second;
        parser.parse(shaderResource->getData(), shaderResource->getSize());
//        parser.dumpDescriptors();

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

            const auto& linkIt = bufferLinks.find(descriptorIt.first);
            if (linkIt != bufferLinks.end()) {
                VkBufferUsageFlagBits usage;
                if (descriptor->descriptorType == VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER) {
                    usage = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
                } else if (descriptor->descriptorType == VK_DESCRIPTOR_TYPE_STORAGE_BUFFER) {
                    usage = VK_BUFFER_USAGE_STORAGE_BUFFER_BIT;
                }
                BufferInfo* linkInfo = &linkIt->second;
                std::shared_ptr<Buffer> buffer = std::make_shared<Buffer>(device, usage, linkInfo->size);
                buffer->create();
                buffers.push_back(buffer);
                linkInfo->buffer = buffer.get();

                VkWriteDescriptorSet descriptorWrite = {};
                descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
                descriptorWrite.dstBinding = layoutBinding.binding;
                descriptorWrite.dstArrayElement = 0;
                descriptorWrite.descriptorType = layoutBinding.descriptorType;
                descriptorWrite.descriptorCount = layoutBinding.descriptorCount;
                descriptorWrite.pBufferInfo = &buffer->descriptorInfo;

                descriptorSets.addWriteDescriptorSet(descriptorWrite);
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
    bufferLinks[name] = linkInfo;
}

void ShaderProgram::write(const std::string& name, VkDeviceSize offset, VkDeviceSize size, void* data) {
    bufferLinks.at(name).buffer->write(offset, size ? size : bufferLinks.at(name).size, data != nullptr ? data : bufferLinks.at(name).uniform);
}

void ShaderProgram::read(const std::string& name, VkDeviceSize offset, VkDeviceSize size, void* data) {
    bufferLinks.at(name).buffer->read(offset, size ? size : bufferLinks.at(name).size, data != nullptr ? data : bufferLinks.at(name).uniform);
}


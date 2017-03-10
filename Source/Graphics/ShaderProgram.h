#pragma once
#include "../Core/Object.h"
#include "../Resource/ShaderResource.h"
#include "Vulkan/Device/Device.h"
#include "Vulkan/Descriptor/DescriptorPool.h"
#include "Vulkan/Descriptor/DescriptorSetLayout.h"
#include "Vulkan/Descriptor/DescriptorSets.h"
#include "UniformBuffer.h"
#include "Vulkan/Buffer.h"
#include "Vulkan/Image/Image.h"
#include <map>

class ShaderProgram : public Object {

public:

    enum class Type {
        VERTEX,
        FRAGMENT,
        COMPUTE
    };

    struct LinkInfo {
        std::string name;
        uint32_t size;
        Vulkan::Buffer* buffer;
        Vulkan::Image* image;
    };

    ShaderProgram(const Vulkan::Device* device);
    ~ShaderProgram();
    void addShader(const std::string& path);
    void createDescriptors();
    void linkBuffer(std::string name, UniformBuffer* uniformBuffer, uint32_t size);

protected:
    std::map<Type, ShaderResource*> shaderResources;

private:
    const Vulkan::Device* device;
    Vulkan::DescriptorPool descriptorPool;
    Vulkan::DescriptorSetLayout descriptorSetLayout;
    Vulkan::DescriptorSets descriptorSets;
    std::map<UniformBuffer*, LinkInfo> uniformLinks;
};

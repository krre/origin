#pragma once
#include "../Core/Object.h"
#include "../Resource/ShaderResource.h"
#include "Vulkan/Device/Device.h"
#include <map>

class ShaderProgram : public Object {

public:

    enum class Type {
        VERTEX,
        FRAGMENT,
        COMPUTE
    };

    ShaderProgram(const Vulkan::Device* device);
    void addShader(const std::string& path);
    void createDescriptors();

protected:
    std::map<Type, ShaderResource*> shaderResources;

private:
    const Vulkan::Device* device;
};

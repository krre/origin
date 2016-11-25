#pragma once
#include "VkObject.h"
#include "Device.h"
#include "ShaderModule.h"

namespace Vulkan {

enum class PipelineType {
    Compute,
    Graphics
};

enum class ShaderType {
    Vertex,
    Fragment
};

class Pipeline : public VkObject {

public:
    Pipeline(PipelineType type, const Device* device);
    ~Pipeline();
    VkPipeline getHandle() const { return handle; }
    bool isValid() const { return handle != VK_NULL_HANDLE; }
    PipelineType getType() const { return type; }
    bool addShaderCode(ShaderType type, size_t size, const uint32_t* code);
    void create();

private:
    VkPipeline handle = VK_NULL_HANDLE;
    const Device* device;
    PipelineType type;
    std::map<ShaderType, std::shared_ptr<Vulkan::ShaderModule>> shaderModules;
};

} // Vulkan

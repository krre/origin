#pragma once
#include "../../Core/Object.h"
#include "../../Resource/ShaderResource.h"
#include "../Vulkan/Device/Device.h"
#include "../Vulkan/Descriptor/DescriptorPool.h"
#include "../Vulkan/Descriptor/DescriptorSetLayout.h"
#include "../Vulkan/Descriptor/DescriptorSets.h"
#include "../Vulkan/Buffer.h"
#include "../Vulkan/Image/Image.h"
#include <map>

class ShaderProgram : public Object {

public:

    enum class Type {
        VERTEX,
        FRAGMENT,
        COMPUTE
    };

    struct BufferInfo {
        uint32_t size;
        void* uniform;
        Vulkan::Buffer* buffer;
    };

    ShaderProgram(const Vulkan::Device* device);
    ~ShaderProgram();
    void addShader(const std::string& path);
    void createDescriptors();
    void linkBuffer(const std::string& name, uint32_t size, void* uniform = nullptr);
    void write(const std::string& name, VkDeviceSize offset = 0, VkDeviceSize size = 0, void* data = nullptr);
    void read(const std::string& name, VkDeviceSize offset = 0, VkDeviceSize size = 0, void* data = nullptr);

protected:
    std::map<Type, ShaderResource*> shaderResources;
    Vulkan::DescriptorSetLayout descriptorSetLayout;
    Vulkan::DescriptorSets descriptorSets;
    std::map<std::string, BufferInfo> bufferInfos;

private:
    const Vulkan::Device* device;
    Vulkan::DescriptorPool descriptorPool;
    std::vector<std::shared_ptr<Vulkan::Buffer>> buffers;
};

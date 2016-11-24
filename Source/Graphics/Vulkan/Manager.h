#pragma once
#include "../../Core/Singleton.h"
#include "Instance.h"
#include "DebugReportCallback.h"
#include "PhysicalDevices.h"
#include "Device.h"
#include "Surface.h"
#include "Queue.h"
#include "Swapchain.h"
#include "ShaderModule.h"
#include <vulkan/vulkan.h>
#include <string>
#include <vector>

const std::string initError = "Vulkan initialization error:\n";

namespace Vulkan {

class Manager : public Singleton<Manager> {

    struct ShaderCode {
        size_t size;
        const uint32_t* code;
    };

public:
    Manager();
    ~Manager();
    bool init();
    void addShaderCode(size_t size, const uint32_t* code);
    std::string getResultDescription() const { return resultDescription; }
    Vulkan::Instance* getInstance() const { return instance.get(); }
    Vulkan::Device* getDevice() const { return device.get(); }
    Vulkan::Surface* getSurface() const { return surface.get(); }

private:
    std::string resultDescription = "None";
    std::vector<ShaderCode> shaderCodes;

    std::unique_ptr<Vulkan::Instance> instance;
    std::unique_ptr<Vulkan::DebugReportCallback> debugCallback;
    std::unique_ptr<Vulkan::PhysicalDevices> physicalDevices;
    std::unique_ptr<Vulkan::Device> device;
    std::unique_ptr<Vulkan::Surface> surface;
    std::unique_ptr<Vulkan::Queue> queue;
    std::unique_ptr<Vulkan::Swapchain> swapchain;
    std::vector<std::shared_ptr<Vulkan::ShaderModule>> shaderModules;
};

} // Vulkan

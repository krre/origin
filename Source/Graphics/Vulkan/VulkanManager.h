#pragma once
#include "../../Core/Singleton.h"
#include "Instance.h"
#include "PhysicalDevices.h"
#include "Device.h"
#include "Surface.h"
#include "Queue.h"
#include <vulkan/vulkan.h>
#include <string>

const std::string initError = "Vulkan initialization error:\n";

class VulkanManager : public Singleton<VulkanManager> {

public:
    VulkanManager();
    ~VulkanManager();
    bool init();
    std::string getResultDescription() const { return resultDescription; }
    Vulkan::Instance* getInstance() const { return instance.get(); }
    Vulkan::Device* getDevice() const { return device.get(); }
    Vulkan::Surface* getSurface() const { return surface.get(); }

private:
    std::string resultDescription = "None";
    std::unique_ptr<Vulkan::Instance> instance;
    std::unique_ptr<Vulkan::PhysicalDevices> physicalDevices;
    std::unique_ptr<Vulkan::Device> device;
    std::unique_ptr<Vulkan::Surface> surface;
    std::unique_ptr<Vulkan::Queue> queue;
};

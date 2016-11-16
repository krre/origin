#pragma once
#include "../../Core/Singleton.h"
#include "Instance.h"
#include "PhysicalDevices.h"
#include "Device.h"
#include <string>

const std::string initError = "Vulkan initialization error\n\n";

class VulkanManager : public Singleton<VulkanManager> {

public:
    VulkanManager();
    bool init();
    std::string getError() const { return error; }

private:
    std::string error = "Undefined error";
    std::unique_ptr<Vulkan::Instance> instance;
    std::unique_ptr<Vulkan::PhysicalDevices> physicalDevices;
    std::unique_ptr<Vulkan::Device> device;
};

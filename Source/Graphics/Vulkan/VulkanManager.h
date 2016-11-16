#pragma once
#include "../../Core/Singleton.h"
#include "Instance.h"
#include "PhysicalDevices.h"
#include "Device.h"
#include <vulkan/vulkan.h>
#include <string>
#include <map>

const std::string initError = "Vulkan initialization error\n\n";

class VulkanManager : public Singleton<VulkanManager> {

public:
    VulkanManager();
    bool init();
    std::string getError() const { return error; }
    Vulkan::Instance* getInstance() const { return instance.get(); }
    Vulkan::Device* getDevice() const { return device.get(); }
    static std::string getResultDescription(VkResult result) { resultDescription.at(result); }

private:
    static std::map<VkResult, std::string> resultDescription;
    std::string error = "Undefined error";
    std::unique_ptr<Vulkan::Instance> instance;
    std::unique_ptr<Vulkan::PhysicalDevices> physicalDevices;
    std::unique_ptr<Vulkan::Device> device;
};
#include "VulkanCore.h"
#include "Graphics/Vulkan/Instance.h"
#include "Graphics/Vulkan/Device/PhysicalDevices.h"
#include "Graphics/Vulkan/Device/PhysicalDevice.h"
#include "Graphics/Vulkan/Device/Device.h"
#include "Graphics/Vulkan/Command/CommandPool.h"

VulkanCore::VulkanCore() {
    instance = std::make_unique<Vulkan::Instance>();
    instance->create();

    physicalDevices = std::make_unique<Vulkan::PhysicalDevices>(instance.get());

    // Create graphics logical device and command pool
    Vulkan::PhysicalDevice* gpd = physicalDevices->findDevice(VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU);
    if (gpd == nullptr) {
        gpd = physicalDevices->findDevice(VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU);
    }

    graphicsDevice = std::make_unique<Vulkan::Device>(gpd);
    graphicsFamily = gpd->findQueueFamily(VK_QUEUE_GRAPHICS_BIT);
    graphicsDevice->addQueueCreateInfo(graphicsFamily, { 1.0 });
    graphicsDevice->create();

    graphicsCommandPool = std::make_shared<Vulkan::CommandPool>(graphicsDevice.get(), graphicsFamily);
    graphicsCommandPool->create();

    // Create compute logical device and command pool
    Vulkan::PhysicalDevice* cpd = physicalDevices->findDevice(VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU);
    if (cpd == nullptr) {
        cpd = physicalDevices->findDevice(VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU);
    }

    computeDevice = std::make_unique<Vulkan::Device>(gpd);
    computeFamily = gpd->findQueueFamily(VK_QUEUE_COMPUTE_BIT);
    computeDevice->addQueueCreateInfo(computeFamily, { 1.0 });
    computeDevice->create();

    computeCommandPool = std::make_shared<Vulkan::CommandPool>(computeDevice.get(), computeFamily);
    computeCommandPool->create();
}

VulkanCore::~VulkanCore() {
    if (graphicsDevice) {
        graphicsDevice->waitIdle();
    }
    if (computeDevice) {
        computeDevice->waitIdle();
    }
}

#include "VulkanCore.h"
#include "Graphics/Vulkan/Wrapper/Instance.h"
#include "Graphics/Vulkan/Wrapper/Device/PhysicalDevices.h"
#include "Graphics/Vulkan/Wrapper/Device/PhysicalDevice.h"
#include "Graphics/Vulkan/Wrapper/Device/Device.h"
#include "Graphics/Vulkan/Wrapper/Command/CommandPool.h"

VulkanCore::VulkanCore() {
    instance = std::make_unique<Vulkan::Instance>();
    instance->create();

    physicalDevices = std::make_unique<Vulkan::PhysicalDevices>(instance->getHandle());
    Vulkan::PhysicalDevice* gpd = physicalDevices->findDevice(VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU);
    if (gpd == nullptr) {
        gpd = physicalDevices->findDevice(VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU);
    }

    graphicsDevice = std::make_unique<Vulkan::Device>(gpd);
    graphicsFamily = gpd->findQueue(VK_QUEUE_GRAPHICS_BIT);
    graphicsDevice->addQueueCreateInfo(graphicsFamily, { 1.0 });
    graphicsDevice->create();

    // TODO: Create compute device;

    commandPool = std::make_shared<Vulkan::CommandPool>(graphicsFamily);
    commandPool->create();
}

VulkanCore::~VulkanCore() {
    if (graphicsDevice) {
        graphicsDevice->waitIdle();
    }
    if (computeDevice) {
        computeDevice->waitIdle();
    }
}

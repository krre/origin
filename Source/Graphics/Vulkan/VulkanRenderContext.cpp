#include "VulkanRenderContext.h"
#include "VulkanRenderWindow.h"
#include "VulkanRenderer.h"
#include "VulkanGpuBuffer.h"
#include "VulkanTexture.h"
#include "VulkanShaderProgram.h"
#include "Debug/DebugEnvironment.h"
#include "Graphics/Vulkan/Wrapper/Instance.h"
#include "Graphics/Vulkan/Wrapper/Device/PhysicalDevices.h"
#include "Graphics/Vulkan/Wrapper/Device/PhysicalDevice.h"
#include "Graphics/Vulkan/Wrapper/Device/Device.h"
#include "Graphics/Vulkan/Wrapper/Command/CommandPool.h"

namespace Origin {

VulkanRenderContext::VulkanRenderContext() {
    instance = std::make_unique<Vulkan::Instance>();

    if (DebugEnvironment::get()->getSettings()["vulkan"]["layers"]["use"]) {
        instance->setEnabledLayers(DebugEnvironment::get()->getSettings()["vulkan"]["layers"]["list"]);
    }

    if (DebugEnvironment::get()->getSettings()["vulkan"]["extensions"]["use"]) {
        instance->setEnabledExtensions(DebugEnvironment::get()->getSettings()["vulkan"]["extensions"]["list"]);
    }

    instance->create();
    createAll();
}

VulkanRenderContext::~VulkanRenderContext() {
    if (graphicsDevice) {
        graphicsDevice->waitIdle();
    }
    if (computeDevice) {
        computeDevice->waitIdle();
    }
}

std::shared_ptr<RenderWindow> VulkanRenderContext::createRenderWindow() {
    std::shared_ptr<RenderWindow> window = std::make_shared<VulkanRenderWindow>(this);
    window->init();
    return window;
}

std::shared_ptr<GpuBuffer> VulkanRenderContext::createGpuBuffer(GpuBuffer::Usage usage, uint32_t size) {
    return std::make_shared<VulkanGpuBuffer>(usage, size);
}

std::shared_ptr<Texture> VulkanRenderContext::createTexture(const std::string& path) {
    return std::make_shared<VulkanTexture>(path);
}

std::shared_ptr<ShaderProgram> VulkanRenderContext::createShaderProgram(const std::string& name) {
    return std::make_shared<VulkanShaderProgram>(name);
}

std::shared_ptr<Renderer> VulkanRenderContext::createRenderer() {
    return std::make_shared<VulkanRenderer>();
}

void VulkanRenderContext::createAll() {
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

} // Origin

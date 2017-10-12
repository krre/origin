#include "VulkanCore.h"
#include "Graphics/Vulkan/Wrapper/Instance.h"
#include "Graphics/Vulkan/Wrapper/Device/Device.h"

VulkanCore::VulkanCore() {
    instance = std::make_unique<Vulkan::Instance>();
    instance->create();
}

VulkanCore::~VulkanCore() {
    instance->getDefaultDevice()->waitIdle();
}

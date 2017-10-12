#include "Devicer.h"
#include "Graphics/Vulkan/Wrapper/Instance.h"
#include "Graphics/Vulkan/VulkanCore.h"

using namespace Vulkan;

Devicer::Devicer(Device* device) : device(device) {
    if (this->device == nullptr) {
        this->device = VulkanCore::get()->getGraphicsDevice();
    }
}

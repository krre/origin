#include "Devicer.h"
#include "Graphics/Render/Vulkan/Wrapper/Instance.h"

using namespace Vulkan;

Devicer::Devicer(Device* device) : device(device) {
    if (this->device == nullptr) {
        this->device = Instance::get()->getDefaultDevice();
    }
}

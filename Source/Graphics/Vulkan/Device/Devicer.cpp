#include "Devicer.h"
#include "../Instance.h"


using namespace Vulkan;

Devicer::Devicer(Device* device) : device(device) {
    if (this->device == nullptr) {
        this->device = Instance::get()->getDefaultDevice();
    }
}

#include "Uniform.h"

using namespace Vulkan;

Uniform::Uniform(const Device* device) : memoryBuffer(device, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT) {

}

#include "CommandBufferSingle.h"
#include "../Manager.h"

using namespace Vulkan;

CommandBufferSingle::CommandBufferSingle(const Device* device) : Devicer(device) {
    commandBuffers = std::make_shared<CommandBuffers>(device, Manager::get()->getCommandPool());
    commandBuffers->allocate(1);

    commandBuffer = std::make_shared<CommandBuffer>(commandBuffers->at(0));
}

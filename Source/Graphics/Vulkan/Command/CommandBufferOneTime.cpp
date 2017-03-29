#include "CommandBufferOneTime.h"
#include "../Manager.h"
#include "../Fence.h"

using namespace Vulkan;

CommandBufferOneTime::CommandBufferOneTime(Device* device) :
        device(device) {
    commandBuffers = std::make_shared<CommandBuffers>(device, Manager::get()->getCommandPool());
    commandBuffers->allocate(1);
    commandBuffer = std::make_shared<CommandBuffer>(commandBuffers->at(0));
}

void CommandBufferOneTime::apply() {
    Fence fence(device);
    fence.create();

    SubmitQueue queue(device, Manager::get()->getGraphicsFamily());
    queue.addCommandBuffer(commandBuffer->getHandle());
    queue.submit(fence.getHandle());

    device->waitForFences({ fence.getHandle() });
}

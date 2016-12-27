#include "CommandBuffers.h"
#include <assert.h>

using namespace Vulkan;

CommandBuffers::CommandBuffers(const Device* device, const CommandPool* commandPool) :
    device(device), commandPool(commandPool) {
    allocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
}

CommandBuffers::~CommandBuffers() {
    vkFreeCommandBuffers(device->getHandle(), commandPool->getHandle(), collection.size(), collection.data());
}

bool CommandBuffers::allocate(uint32_t count) {
    assert(collection.size() == 0 && count > 0);
    collection.resize(count);
    allocateInfo.commandPool = commandPool->getHandle();
    allocateInfo.commandBufferCount = count;

    return checkError(vkAllocateCommandBuffers(device->getHandle(), &allocateInfo, collection.data()), "Failed to allocate command buffers");
}
